﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/TextureRegion.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>
# include "MSDFGlyphCache.hpp"

namespace s3d
{
	RectF MSDFGlyphCache::draw(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const bool usebasePos, const Vec2& pos, const double size, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		if (not prerender(font, clusters))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const bool noScaling = (size == prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		for (const auto& cluster : clusters)
		{
			if (ProcessControlCharacter(s[cluster.pos], penPos, lineCount, basePos, scale, lineHeightScale, prop))
			{
				xMax = Max(xMax, penPos.x);
				continue;
			}

			if (cluster.fontIndex != 0)
			{
				const size_t fallbackIndex = (cluster.fontIndex - 1);
				RectF rect;

				if (usebasePos)
				{
					rect = SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos, size, textStyle, color, lineHeightScale);
				}
				else
				{
					rect = SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos.movedBy(0, prop.ascender * scale), size, textStyle, color, lineHeightScale);
				}

				penPos.x += rect.w;
				xMax = Max(xMax, penPos.x);
				continue;
			}

			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			{
				const TextureRegion textureRegion = m_texture(cache.textureRegionLeft, cache.textureRegionTop, cache.textureRegionWidth, cache.textureRegionHeight);
				const Vec2 posOffset = usebasePos ? cache.info.getBase(scale) : cache.info.getOffset(scale);
				const Vec2 drawPos = (penPos + posOffset);

				if (noScaling)
				{
					textureRegion
						.draw(drawPos, color);
				}
				else
				{
					textureRegion
						.scaled(scale)
						.draw(drawPos, color);
				}
			}

			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}

	bool MSDFGlyphCache::draw(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const RectF& area, const double size, const TextStyle& textStyle, const ColorF& color, const double lineHeightScale)
	{
		if (not prerender(font, clusters))
		{
			return false;
		}

		// 「.」のグリフ
		const Array<GlyphCluster> dotGlyphCluster = font.getGlyphClusters(U".", false);
		if (not prerender(font, dotGlyphCluster))
		{
			// do tnohing
		}
		const double dotXAdvance = m_glyphTable.find(dotGlyphCluster[0].glyphIndex)->second.info.xAdvance;
		const Vec2 areaBottomRight = area.br();

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const double lineHeight = (prop.height() * scale * lineHeightScale);

		if ((area.w < (dotXAdvance * 3)) || (area.h < lineHeight))
		{
			return false;
		}

		const int32 maxLines = Max(static_cast<int32>(area.h / (lineHeight ? lineHeight : 1)), 1);
		const Vec2 basePos{ area.pos };

		Array<Vec2> penPositions;
		size_t clusterIndex = 0;
		{
			Array<double> xAdvances(Arg::reserve = clusters.size());
			Vec2 penPos{ basePos };
			int32 lineIndex = 0;
			double currentLineWidth = 0.0;
			double previousLineWidth = 0.0;

			for (; clusterIndex < clusters.size(); ++clusterIndex)
			{
				const auto& cluster = clusters[clusterIndex];
				double xAdvance = 0.0;
				bool nextLine = false;

				if (const char32 ch = s[cluster.pos];
					IsControl(ch))
				{
					if (ch == U'\t')
					{
						xAdvance = Min((prop.spaceWidth * scale * 4), (areaBottomRight.x - penPos.x));
					}
					else
					{
						xAdvance = 0.0;
						nextLine = (ch == U'\n');
					}
				}
				else if (cluster.fontIndex != 0)
				{
					const size_t fallbackIndex = (cluster.fontIndex - 1);
					xAdvance = SIV3D_ENGINE(Font)->regionBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos.movedBy(0, prop.ascender * scale), size, lineHeightScale).w;
				}
				else
				{
					const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
					xAdvance = (cache.info.xAdvance * scale);
				}

				if (areaBottomRight.x < (penPos.x + xAdvance))
				{
					nextLine = true;
				}

				if (nextLine)
				{
					++lineIndex;
					previousLineWidth = currentLineWidth;

					penPos.x = basePos.x;
					penPos.y = basePos.y + (lineIndex * lineHeight);
				}

				penPositions << penPos;
				xAdvances << xAdvance;
				penPos.x += xAdvance;
				currentLineWidth = (penPos.x - penPos.x);

				// エリア外
				if (maxLines <= lineIndex)
				{
					const double dotsWidth = (dotXAdvance * 3);
					double xEliminatedWidth = (area.w - previousLineWidth);

					while (clusterIndex > 0)
					{
						xEliminatedWidth += xAdvances[clusterIndex];
						--clusterIndex;

						if (dotsWidth <= xEliminatedWidth)
						{
							break;
						}
					}

					break;
				}
			}
		}

		String newText;
		Array<GlyphCluster> newClusters;
		Array<Vec2> newPenPositions;

		if (clusterIndex == clusters.size())
		{
			newText = s;
			newClusters = clusters;
			newPenPositions = std::move(penPositions);
		}
		else
		{
			const StringView v = s.substr(0, clusters[clusterIndex].pos + 1);
			newText.reserve(v.size() + 3);
			newText.append(v);
			newText.append(U"...");

			newClusters = clusters.take(clusterIndex);

			newClusters.push_back(dotGlyphCluster.front());
			newClusters.back().pos = (newText.size() - 3);

			newClusters.push_back(dotGlyphCluster.front());
			newClusters.back().pos = (newText.size() - 2);

			newClusters.push_back(dotGlyphCluster.front());
			newClusters.back().pos = (newText.size() - 1);

			newPenPositions = std::move(penPositions);
			newPenPositions.resize(clusterIndex + 1);
			newPenPositions << newPenPositions.back().movedBy(dotXAdvance, 0);
			newPenPositions << newPenPositions.back().movedBy(dotXAdvance, 0);
		}

		const bool noScaling = (size == prop.fontPixelSize);

		for (size_t i = 0; i < newClusters.size(); ++i)
		{
			const auto& cluster = newClusters[i];

			if (IsControl(newText[cluster.pos]))
			{
				continue;
			}
			else if (cluster.fontIndex != 0)
			{
				const size_t fallbackIndex = (cluster.fontIndex - 1);
				SIV3D_ENGINE(Font)->drawBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
					cluster, newPenPositions[i].movedBy(0, prop.ascender * scale), size, textStyle, color, lineHeightScale);
			}
			else
			{
				const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
				{
					const TextureRegion textureRegion = m_texture(cache.textureRegionLeft, cache.textureRegionTop, cache.textureRegionWidth, cache.textureRegionHeight);
					const Vec2 posOffset = cache.info.getOffset(scale);
					const Vec2 drawPos = (newPenPositions[i] + posOffset);

					if (noScaling)
					{
						textureRegion
							.draw(drawPos, color);
					}
					else
					{
						textureRegion
							.scaled(scale)
							.draw(drawPos, color);
					}
				}
			}
		}

		return (clusterIndex == clusters.size());
	}

	RectF MSDFGlyphCache::drawFallback(const FontData& font, const GlyphCluster& cluster, const bool usebasePos, const Vec2& pos, const double size, const ColorF& color, const double lineHeightScale)
	{
		if (not prerender(font, { cluster }))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const bool noScaling = (size == prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		{
			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			{
				const TextureRegion textureRegion = m_texture(cache.textureRegionLeft, cache.textureRegionTop, cache.textureRegionWidth, cache.textureRegionHeight);
				const Vec2 posOffset = usebasePos ? cache.info.getBase(scale) : cache.info.getOffset(scale);
				const Vec2 drawPos = (penPos + posOffset);
				RectF rect;

				if (noScaling)
				{
					rect = textureRegion
						.draw(drawPos, color);
				}
				else
				{
					rect = textureRegion
						.scaled(scale)
						.draw(drawPos, color);
				}
			}

			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}

	Array<double> MSDFGlyphCache::getXAdvances(const FontData& font, StringView s, const Array<GlyphCluster>& clusters)
	{
		if (not prerender(font, clusters))
		{
			return{};
		}

		const auto& prop = font.getProperty();
		Array<double> xAdvances(Arg::reserve = clusters.size());

		for (const auto& cluster : clusters)
		{
			const char32 ch = s[cluster.pos];

			if (IsControl(ch))
			{
				if (ch == U'\t')
				{
					xAdvances << (prop.spaceWidth * 4);
				}
				else
				{
					xAdvances << 0.0;
				}

				continue;
			}

			if (cluster.fontIndex != 0)
			{
				const size_t fallbackIndex = (cluster.fontIndex - 1);

				xAdvances << SIV3D_ENGINE(Font)->xAdvanceFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
					cluster);

				continue;
			}

			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			xAdvances << cache.info.xAdvance;
		}

		return xAdvances;
	}

	double MSDFGlyphCache::xAdvanceFallback(const FontData& font, const GlyphCluster& cluster)
	{
		if (not prerender(font, { cluster }))
		{
			return 0.0;
		}

		const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
		return cache.info.xAdvance;
	}

	RectF MSDFGlyphCache::region(const FontData& font, const StringView s, const Array<GlyphCluster>& clusters, const bool usebasePos, const Vec2& pos, const double size, const double lineHeightScale)
	{
		if (not prerender(font, clusters))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		for (const auto& cluster : clusters)
		{
			if (ProcessControlCharacter(s[cluster.pos], penPos, lineCount, basePos, scale, lineHeightScale, prop))
			{
				xMax = Max(xMax, penPos.x);
				continue;
			}

			if (cluster.fontIndex != 0)
			{
				const size_t fallbackIndex = (cluster.fontIndex - 1);
				RectF rect;

				if (usebasePos)
				{
					rect = SIV3D_ENGINE(Font)->regionBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos, size, lineHeightScale);
				}
				else
				{
					rect = SIV3D_ENGINE(Font)->regionBaseFallback(font.getFallbackFont(fallbackIndex).lock()->id(),
						cluster, penPos.movedBy(0, prop.ascender * scale), size, lineHeightScale);
				}

				penPos.x += rect.w;
				xMax = Max(xMax, penPos.x);
				continue;
			}

			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}

	RectF MSDFGlyphCache::regionFallback(const FontData& font, const GlyphCluster& cluster, const bool usebasePos, const Vec2& pos, const double size, const double lineHeightScale)
	{
		if (not prerender(font, { cluster }))
		{
			return RectF{ 0 };
		}

		const auto& prop = font.getProperty();
		const double scale = (size / prop.fontPixelSize);
		const Vec2 basePos{ pos };
		Vec2 penPos{ basePos };
		int32 lineCount = 1;
		double xMax = basePos.x;

		{
			const auto& cache = m_glyphTable.find(cluster.glyphIndex)->second;
			penPos.x += (cache.info.xAdvance * scale);
			xMax = Max(xMax, penPos.x);
		}

		const Vec2 topLeft = (usebasePos ? pos.movedBy(0, -prop.ascender * scale) : pos);
		return{ topLeft, (xMax - basePos.x), (lineCount * prop.height() * scale * lineHeightScale) };
	}

	void MSDFGlyphCache::setBufferWidth(const int32 width)
	{
		m_buffer.bufferWidth = Max(width, 0);
	}

	int32 MSDFGlyphCache::getBufferWidth() const noexcept
	{
		return m_buffer.bufferWidth;
	}

	bool MSDFGlyphCache::preload(const FontData& font, const StringView s)
	{
		return prerender(font, font.getGlyphClusters(s, false));
	}

	const Texture& MSDFGlyphCache::getTexture() const noexcept
	{
		return m_texture;
	}

	TextureRegion MSDFGlyphCache::getTextureRegion(const FontData& font, const GlyphIndex glyphIndex)
	{
		if (not prerender(font, { GlyphCluster{.glyphIndex = glyphIndex } }))
		{
			return{};
		}

		const auto& cache = m_glyphTable.find(glyphIndex)->second;
		return m_texture(cache.textureRegionLeft, cache.textureRegionTop, cache.textureRegionWidth, cache.textureRegionHeight);
	}

	bool MSDFGlyphCache::prerender(const FontData& font, const Array<GlyphCluster>& clusters)
	{
		bool hasDirty = false;

		if (m_glyphTable.empty())
		{
			const MSDFGlyph glyph = font.renderMSDFByGlyphIndex(0, m_buffer.bufferWidth);

			if (not CacheGlyph(font, glyph.image, glyph, m_buffer, m_glyphTable))
			{
				return false;
			}

			hasDirty = true;
		}

		for (const auto& cluster : clusters)
		{
			if (m_glyphTable.contains(cluster.glyphIndex))
			{
				continue;
			}

			const MSDFGlyph glyph = font.renderMSDFByGlyphIndex(cluster.glyphIndex, m_buffer.bufferWidth);

			if (m_glyphTable.contains(glyph.glyphIndex))
			{
				continue;
			}

			if (not CacheGlyph(font, glyph.image, glyph, m_buffer, m_glyphTable))
			{
				return false;
			}

			hasDirty = true;
		}

		if (hasDirty)
		{
			m_texture.fill(m_buffer.image);
		}

		return true;
	}
}