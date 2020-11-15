﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

namespace s3d
{
	inline Vec2 RandomVec2()
	{
		return RandomVec2(GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(URBG&& urbg)
	{
		const double theta = Random(Math::Constants::TwoPi, std::forward<URBG>(urbg));
		return{ std::cos(theta), std::sin(theta) };
	}

	inline Vec2 RandomVec2(const double length)
	{
		return RandomVec2(length, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const double length, URBG&& urbg)
	{
		return RandomVec2(std::forward<URBG>(urbg)) * length;
	}

	inline Vec2 RandomVec2(const double x, const std::pair<double, double>& yMinMax)
	{
		return RandomVec2(x, yMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const double x, const std::pair<double, double>& yMinMax, URBG&& urbg)
	{
		return{ x, Random(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)) };
	}

	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const double y)
	{
		return RandomVec2(xMinMax, y, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const double y, URBG&& urbg)
	{
		return{ Random(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)), y };
	}

	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax)
	{
		return RandomVec2(xMinMax, yMinMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const std::pair<double, double>& xMinMax, const std::pair<double, double>& yMinMax, URBG&& urbg)
	{
		return{ Random(xMinMax.first, xMinMax.second, std::forward<URBG>(urbg)),
				Random(yMinMax.first, yMinMax.second, std::forward<URBG>(urbg)) };
	}

	inline Vec2 RandomVec2(const double xMax, const double yMax)
	{
		return RandomVec2(xMax, yMax, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const double xMax, const double yMax, URBG&& urbg)
	{
		return{ Random(xMax, std::forward<URBG>(urbg)),
				Random(yMax, std::forward<URBG>(urbg)) };
	}

	inline Vec2 RandomVec2(const Circle& circle)
	{
		return RandomVec2(circle, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const Circle& circle, URBG&& urbg)
	{
		const double r = (std::sqrt(Random(std::forward<URBG>(urbg))) * circle.r);
		const double theta = Random(Math::Constants::TwoPi, std::forward<URBG>(urbg));
		return circle.center.movedBy((std::cos(theta) * r), (std::sin(theta) * r));
	}

	inline Vec2 RandomVec2(const RectF& rect)
	{
		return RandomVec2(rect, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const RectF& rect, URBG&& urbg)
	{
		return{ Random(rect.x, (rect.x + rect.w), std::forward<URBG>(urbg)),
				Random(rect.y, (rect.y + rect.h), std::forward<URBG>(urbg)) };
	}

	inline Vec2 RandomVec2(const Triangle& triangle)
	{
		return RandomVec2(triangle, GetDefaultRNG());
	}

	SIV3D_CONCEPT_URBG_
	inline Vec2 RandomVec2(const Triangle& triangle, URBG&& urbg)
	{
		const Vec2 v0 = (triangle.p1 - triangle.p0);
		const Vec2 v1 = (triangle.p2 - triangle.p0);

		double u = Random(std::forward<URBG>(urbg));
		double v = Random(std::forward<URBG>(urbg));

		if (u + v > 1.0)
		{
			u = (1.0 - u);
			v = (1.0 - v);
		}

		return (triangle.p0 + u * v0 + v * v1);
	}
}