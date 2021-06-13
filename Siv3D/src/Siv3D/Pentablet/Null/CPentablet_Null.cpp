//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CPentablet_Null.hpp"
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CPentablet_Null::CPentablet_Null()
	{

	}

	CPentablet_Null::~CPentablet_Null()
	{
		LOG_SCOPED_TRACE(U"CPentablet_Null::~CPentablet_Null()");
	}

	void CPentablet_Null::init()
	{
		LOG_SCOPED_TRACE(U"CPentablet_Null::init()");
	}

	void CPentablet_Null::update()
	{

	}
}