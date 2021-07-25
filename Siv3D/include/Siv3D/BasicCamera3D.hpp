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

# pragma once
# include "Common.hpp"
# include "PointVector.hpp"
# include "Scene.hpp"
# include "Ray.hpp"
# include "Mat4x4.hpp"

namespace s3d
{
	class alignas(16) BasicCamera3D
	{
	public:

		static constexpr double DefaultVerticalFOV = 30_deg;

		static constexpr double DefaultNearClip = 0.1;

		BasicCamera3D() = default;

		BasicCamera3D(const BasicCamera3D&) = default;

		explicit BasicCamera3D(const Size& sceneSize, double verticalFOV = DefaultVerticalFOV, const Vec3& eyePosition = Vec3{ 0, 4, -4 }, const Vec3& focusPosition = Vec3{ 0, 0, 0 }, const Vec3& upDirection = Vec3{ 0, 1, 0 }, double nearClip = DefaultNearClip) noexcept;

		virtual ~BasicCamera3D() = default;

		[[nodiscard]]
		virtual Mat4x4 getMat4x4() const;

		void setSceneSize(const Size& sceneSize) noexcept;

		void setProjection(const Size& sceneSize, double verticalFOV, double nearClip = DefaultNearClip) noexcept;

		void setView(const Vec3& eyePosition, const Vec3& focusPosition, const Vec3& upDirection = Vec3{ 0, 1, 0 }) noexcept;

		[[nodiscard]]
		const Size& getSceneSize() const noexcept;

		[[nodiscard]]
		double getVerticlaFOV() const noexcept;

		[[nodiscard]]
		double getNearClip() const noexcept;

		[[nodiscard]]
		const Vec3& getEyePosition() const noexcept;

		[[nodiscard]]
		const Vec3& getFocusPosition() const noexcept;

		[[nodiscard]]
		const Vec3& getUpDirection() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getProj() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getView() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getViewProj() const noexcept;

		[[nodiscard]]
		const Mat4x4& SIV3D_VECTOR_CALL getInvViewProj() const noexcept;

		[[nodiscard]]
		Float3 worldToScreenPoint(const Float3& pos) const noexcept;

		[[nodiscard]]
		Float3 screenToWorldPoint(const Float2& pos, float depth) const noexcept;

		[[nodiscard]]
		Ray screenToRay(const Vec2& pos) const noexcept;

	protected:

		Mat4x4 m_proj = Mat4x4::Identity();

		Mat4x4 m_view = Mat4x4::Identity();

		Mat4x4 m_viewProj = Mat4x4::Identity();

		Mat4x4 m_invViewProj = Mat4x4::Identity();

		//
		// Proj
		//
		Size m_sceneSize = Scene::Size();

		double m_verticalFOV = DefaultVerticalFOV;

		double m_nearClip = DefaultNearClip;

		//
		// View
		//
		Vec3 m_eyePosition = Vec3{ 0, 4, -4 };

		Vec3 m_focusPosition = Vec3{ 0, 0, 0 };

		Vec3 m_upDirection = Vec3{ 0, 1, 0 };

		void updateProj() noexcept;

		void updateView() noexcept;

		void updateViewProj() noexcept;
	};
}

# include "detail/BasicCamera3D.ipp"