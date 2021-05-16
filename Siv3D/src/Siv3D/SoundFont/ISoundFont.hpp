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
# include <Siv3D/Common.hpp>
# include <Siv3D/GMInstrument.hpp>
# include <Siv3D/MIDINote.hpp>
# include <Siv3D/Wave.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DSoundFont
	{
	public:

		static ISiv3DSoundFont* Create();

		virtual ~ISiv3DSoundFont() = default;

		virtual void init() = 0;

		virtual Wave render(GMInstrument instrument, uint8 key, const Duration& noteOn, const Duration& noteOff, double velocity, Arg::samplingRate_<uint32> samplingRate) = 0;

		virtual Wave renderMIDI(FilePathView path, std::array<Array<MIDINote>, 16>& midiScore, Arg::samplingRate_<uint32> samplingRate, const Duration& tail) = 0;

		virtual Wave renderMIDI(IReader& reader, std::array<Array<MIDINote>, 16>& midiScore, Arg::samplingRate_<uint32> samplingRate, const Duration& tail) = 0;
	};
}