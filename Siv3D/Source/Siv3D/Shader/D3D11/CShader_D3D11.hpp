﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include <d3dcompiler.h>
# include "../IShader.hpp"
# include "VertexShader_D3D11.hpp"
# include "../../AssetHandleManager/AssetHandleManager.hpp"

namespace s3d
{
	class CShader_D3D11 : public ISiv3DShader
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		HINSTANCE m_d3dcompiler = nullptr;

		decltype(D3DCompile2)* p_D3DCompile2 = nullptr;

		AssetHandleManager<VertexShader::IDType, std::shared_ptr<VertexShader_D3D11>> m_vertexShaders{ L"VertexShader" };

		bool compileHLSL(IReader& reader, ByteArray& to, const std::string& entryPoint, const std::string& target);

	public:

		CShader_D3D11();

		~CShader_D3D11() override;

		bool init(ID3D11Device* device, ID3D11DeviceContext* context);

		VertexShader::IDType createVS(IReader&& reader) override;

		PixelShader::IDType createPS(IReader&& reader) override { return 0; }

		void releaseVS(VertexShader::IDType handleID) override {}

		void releasePS(PixelShader::IDType handleID) override {}
	};
}

# endif
