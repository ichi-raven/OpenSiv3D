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

# include <Siv3D/DrawableText.hpp>
# include <Siv3D/Font/IFont.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>

namespace s3d
{
	DrawableText::DrawableText(const Font& _font, const String& _text)
		: font{ _font }
		, text{ _text }
		, cluster{ font.getGlyphClusters(text) } {}

	DrawableText::DrawableText(const Font& _font, String&& _text)
		: font{ _font }
		, text{ std::move(_text) }
		, cluster{ font.getGlyphClusters(text) } {}

	Array<double> DrawableText::getXAdvances() const
	{
		return SIV3D_ENGINE(Font)->getXAdvances(font.id(), text, cluster);
	}

	RectF DrawableText::region(const double x, const double y) const
	{
		return region(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::region(const Vec2 pos) const
	{
		return region(font.fontSize(), pos);
	}

	RectF DrawableText::region(const double size, const double x, const double y) const
	{
		return region(size, Vec2{ x, y });
	}

	RectF DrawableText::region(const Arg::topLeft_<Vec2> topLeft) const
	{
		return region(font.fontSize(), topLeft);
	}

	RectF DrawableText::region(const Arg::topCenter_<Vec2> topCenter) const
	{
		return region(font.fontSize(), topCenter);
	}

	RectF DrawableText::region(const Arg::topRight_<Vec2> topRight) const
	{
		return region(font.fontSize(), topRight);
	}

	RectF DrawableText::region(const Arg::rightCenter_<Vec2> rightCenter) const
	{
		return region(font.fontSize(), rightCenter);
	}

	RectF DrawableText::region(const Arg::bottomRight_<Vec2> bottomRight) const
	{
		return region(font.fontSize(), bottomRight);
	}

	RectF DrawableText::region(const Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		return region(font.fontSize(), bottomCenter);
	}

	RectF DrawableText::region(const Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return region(font.fontSize(), bottomLeft);
	}

	RectF DrawableText::region(const Arg::leftCenter_<Vec2> leftCenter) const
	{
		return region(font.fontSize(), leftCenter);
	}

	RectF DrawableText::region(const Arg::center_<Vec2> center) const
	{
		return region(font.fontSize(), center);
	}

	RectF DrawableText::region(const double size, const Vec2 pos) const
	{
		return SIV3D_ENGINE(Font)->region(font.id(), text, cluster, pos, size, 1.0);
	}

	RectF DrawableText::region(const double size, const Arg::topLeft_<Vec2> topLeft) const
	{
		return region(size, *topLeft);
	}

	RectF DrawableText::region(const double size, const Arg::topCenter_<Vec2> topCenter) const
	{
		return region(size, topCenter->movedBy(-region().w * 0.5, 0));
	}

	RectF DrawableText::region(const double size, const Arg::topRight_<Vec2> topRight) const
	{
		return region(size, topRight->movedBy(-region().w, 0));
	}

	RectF DrawableText::region(const double size, const Arg::rightCenter_<Vec2> rightCenter) const
	{
		return region(size, rightCenter->movedBy(-region().w, -region().h * 0.5));
	}

	RectF DrawableText::region(const double size, const Arg::bottomRight_<Vec2> bottomRight) const
	{
		return region(size, bottomRight->movedBy(-region().size));
	}

	RectF DrawableText::region(const double size, const Arg::bottomCenter_<Vec2> bottomCenter) const
	{
		return region(size, bottomCenter->movedBy(-region().w * 0.5, -region().h));
	}

	RectF DrawableText::region(const double size, const Arg::bottomLeft_<Vec2> bottomLeft) const
	{
		return region(size, bottomLeft->movedBy(0, -region().h));
	}

	RectF DrawableText::region(const double size, const Arg::leftCenter_<Vec2> leftCenter) const
	{
		return region(size, leftCenter->movedBy(0, -region().h * 0.5));
	}

	RectF DrawableText::region(const double size, const Arg::center_<Vec2> center) const
	{
		return regionAt(size, *center);
	}

	RectF DrawableText::regionBase(const double x, const double y) const
	{
		return regionBase(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionBase(const Vec2 pos) const
	{
		return regionBase(font.fontSize(), pos);
	}

	RectF DrawableText::regionBase(const double size, const double x, const double y) const
	{
		return regionBase(size, Vec2{ x, y });
	}

	RectF DrawableText::regionBase(const double size, const Vec2 pos) const
	{
		return SIV3D_ENGINE(Font)->regionBase(font.id(), text, cluster, pos, size, 1.0);
	}

	RectF DrawableText::regionAt(const double x, const double y) const
	{
		return regionAt(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionAt(const Vec2 pos) const
	{
		return regionAt(font.fontSize(), pos);
	}

	RectF DrawableText::regionAt(const double size, const double x, const double y) const
	{
		return regionAt(size, Vec2{ x, y });
	}

	RectF DrawableText::regionAt(const double size, const Vec2 pos) const
	{
		const RectF rect = region(size, Vec2{ 0, 0 });

		return rect.movedBy(pos - rect.center());
	}

	RectF DrawableText::regionBaseAt(const double x, const double y) const
	{
		return regionBaseAt(font.fontSize(), Vec2{ x, y });
	}

	RectF DrawableText::regionBaseAt(const Vec2 pos) const
	{
		return regionBaseAt(font.fontSize(), pos);
	}

	RectF DrawableText::regionBaseAt(const double size, const double x, const double y) const
	{
		return regionBaseAt(size, Vec2{ x, y });
	}

	RectF DrawableText::regionBaseAt(const double size, const Vec2 pos) const
	{
		const RectF rect = regionBase(size, Vec2{ 0, 0 });

		return rect.movedBy(pos.x - (rect.w * 0.5), pos.y);
	}

	RectF DrawableText::draw(const double x, const double y, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const Vec2& pos, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), pos, color);
	}

	RectF DrawableText::draw(const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), topLeft, color);
	}

	RectF DrawableText::draw(const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), topCenter, color);
	}

	RectF DrawableText::draw(const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), topRight, color);
	}

	RectF DrawableText::draw(const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), rightCenter, color);
	}

	RectF DrawableText::draw(const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), bottomRight, color);
	}

	RectF DrawableText::draw(const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), bottomCenter, color);
	}

	RectF DrawableText::draw(const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), bottomLeft, color);
	}

	RectF DrawableText::draw(const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), leftCenter, color);
	}

	RectF DrawableText::draw(const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), center, color);
	}

	bool DrawableText::draw(const RectF& area, const ColorF& color) const
	{
		return draw(TextStyle::Default, font.fontSize(), area, color);
	}

	RectF DrawableText::draw(const double size, const double x, const double y, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const double size, const Vec2& pos, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, pos, color);
	}

	RectF DrawableText::draw(const double size, const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, topLeft, color);
	}

	RectF DrawableText::draw(const double size, const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, topCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, topRight, color);
	}

	RectF DrawableText::draw(const double size, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, rightCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, bottomRight, color);
	}

	RectF DrawableText::draw(const double size, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, bottomCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, bottomLeft, color);
	}

	RectF DrawableText::draw(const double size, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, leftCenter, color);
	}

	RectF DrawableText::draw(const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, center, color);
	}

	bool DrawableText::draw(const double size, const RectF& area, const ColorF& color) const
	{
		return draw(TextStyle::Default, size, area, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), topLeft, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), topCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), topRight, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), rightCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), bottomRight, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), bottomCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), bottomLeft, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), leftCenter, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), center, color);
	}

	bool DrawableText::draw(const TextStyle& textStyle, const RectF& area, const ColorF& color) const
	{
		return draw(textStyle, font.fontSize(), area, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return draw(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->draw(font.id(), text, cluster, pos, size, textStyle, color, 1.0);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::topLeft_<Vec2> topLeft, const ColorF& color) const
	{
		return draw(textStyle, size, *topLeft, color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::topCenter_<Vec2> topCenter, const ColorF& color) const
	{
		return draw(textStyle, size, topCenter->movedBy(-region().w * 0.5, 0), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::topRight_<Vec2> topRight, const ColorF& color) const
	{
		return draw(textStyle, size, topRight->movedBy(-region().w, 0), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::rightCenter_<Vec2> rightCenter, const ColorF& color) const
	{
		return draw(textStyle, size, rightCenter->movedBy(-region().w, -region().h * 0.5), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::bottomRight_<Vec2> bottomRight, const ColorF& color) const
	{
		return draw(textStyle, size, bottomRight->movedBy(-region().size), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::bottomCenter_<Vec2> bottomCenter, const ColorF& color) const
	{
		return draw(textStyle, size, bottomCenter->movedBy(-region().w * 0.5, -region().h), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::bottomLeft_<Vec2> bottomLeft, const ColorF& color) const
	{
		return draw(textStyle, size, bottomLeft->movedBy(0, -region().h), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::leftCenter_<Vec2> leftCenter, const ColorF& color) const
	{
		return draw(textStyle, size, leftCenter->movedBy(0, -region().h * 0.5), color);
	}

	RectF DrawableText::draw(const TextStyle& textStyle, const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawAt(textStyle, size, *center, color);
	}

	bool DrawableText::draw(const TextStyle& textStyle, const double size, const RectF& area, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->draw(font.id(), text, cluster, area, size, textStyle, color, 1.0);
	}

	RectF DrawableText::drawBase(const double x, const double y, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const Vec2& pos, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBase(const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, font.fontSize(), left, color);
	}

	RectF DrawableText::drawBase(const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, font.fontSize(), center, color);
	}

	RectF DrawableText::drawBase(const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, font.fontSize(), right, color);
	}

	RectF DrawableText::drawBase(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, size, pos, color);
	}

	RectF DrawableText::drawBase(const double size, const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, size, left, color);
	}

	RectF DrawableText::drawBase(const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, size, center, color);
	}

	RectF DrawableText::drawBase(const double size, const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(TextStyle::Default, size, right, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), left, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), center, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(textStyle, font.fontSize(), right, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBase(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		return SIV3D_ENGINE(Font)->drawBase(font.id(), text, cluster, pos, size, textStyle, color, 1.0);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Arg::left_<Vec2> left, const ColorF& color) const
	{
		return drawBase(textStyle, size, *left, color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Arg::center_<Vec2> center, const ColorF& color) const
	{
		return drawBase(textStyle, size, center->movedBy(-region().w * 0.5, 0), color);
	}

	RectF DrawableText::drawBase(const TextStyle& textStyle, const double size, const Arg::right_<Vec2> right, const ColorF& color) const
	{
		return drawBase(textStyle, size, right->movedBy(-region().w, 0), color);
	}

	RectF DrawableText::drawAt(const double x, const double y, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const Vec2& pos, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawAt(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawAt(TextStyle::Default, size, pos, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawAt(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawAt(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawAt(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawAt(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		const RectF rect = region(size, Vec2{ 0, 0 });

		const Vec2 drawPos = (pos - rect.center());

		return draw(textStyle, size, drawPos, color);
	}

	RectF DrawableText::drawBaseAt(const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBaseAt(const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const double size, const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(TextStyle::Default, size, pos, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(textStyle, font.fontSize(), Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const Vec2& pos, const ColorF& color) const
	{
		return drawBaseAt(textStyle, font.fontSize(), pos, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double size, const double x, const double y, const ColorF& color) const
	{
		return drawBaseAt(textStyle, size, Vec2{ x, y }, color);
	}

	RectF DrawableText::drawBaseAt(const TextStyle& textStyle, const double size, const Vec2& pos, const ColorF& color) const
	{
		const RectF rect = regionBase(size, Vec2{ 0, 0 });

		const double drawPosX = (pos.x - (rect.w * 0.5));

		return drawBase(textStyle, size, Vec2{ drawPosX, pos.y }, color);
	}
}