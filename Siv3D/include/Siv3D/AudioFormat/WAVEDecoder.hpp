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
# include <Siv3D/IAudioDecoder.hpp>

namespace s3d
{
	/// @brief WAVE 形式音声データのデコーダ
	class WAVEDecoder : public IAudioDecoder
	{
	public:

		/// @brief デコーダの対応形式 `U"WAVE"` を返します。
		/// @return 文字列 `U"WAVE"`
		[[nodiscard]]
		StringView name() const override;

		/// @brief WAVE 形式の先頭データであるかを返します。
		/// @param bytes データの先頭 48 バイト
		/// @return WAVE 形式と推測される場合 true, それ以外の場合は false
		[[nodiscard]]
		bool isHeader(const uint8(&bytes)[48]) const override;

		/// @brief WAVE 形式のファイルに想定される拡張子一覧 `{ U"wav" }` を返します。
		/// @return 配列 `{ U"wav" }`
		[[nodiscard]]
		const Array<String>& possibleExtensions() const override;

		/// @brief WAVE 形式を示す AudioFormat を返します。
		/// @return `AudioFormat::WAVE`
		[[nodiscard]]
		AudioFormat audioFormat() const noexcept override;

		/// @brief WAVE 形式の音声ファイルをデコードして Wave を作成します。
		/// @param path 音声ファイルのパス
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(FilePathView path) const override;

		/// @brief WAVE 形式の音声データをデコードして Wave を作成します。
		/// @param reader 音声データの IReader インタフェース
		/// @param pathHint ファイルパス（オプション）
		/// @return 作成した Wave
		[[nodiscard]]
		Wave decode(IReader& reader, FilePathView pathHint = {}) const override;
	};
}