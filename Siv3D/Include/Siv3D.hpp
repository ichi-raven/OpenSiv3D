﻿//----------------------------------------------------------------------------------------
//
//	Copyright (c) 2008-2016 Ryo Suzuki
//	Copyright (c) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files(the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions :
//	
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//	
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//
//----------------------------------------------------------------------------------------

# pragma once
# ifndef SIV3D_INCLUDED
	# define SIV3D_INCLUDED
# endif

# include "Siv3D/Platform.hpp"
# if defined(SIV3D_TARGET_WINDOWS)
	# include "Siv3D/PlatformWindows.hpp"
# endif

//
// ユーティリティ
//
	// ライブラリのバージョン
	# include "Siv3D/Version.hpp"
	// 型
	# include "Siv3D/Types.hpp"
	// 前方宣言
	# include "Siv3D/Fwd.hpp"
	// ユーティリティ
	# include "Siv3D/Utility.hpp"
	// ハッシュ
	# include "Siv3D/Hash.hpp"
	// ファンクタ
	# include "Siv3D/Functor.hpp"
	// コンセプト
	# include "Siv3D/Concept.hpp"
	// コピー禁止クラス
	# include "Siv3D/Uncopyable.hpp"
	// 名前付き引数
	# include "Siv3D/NamedParameter.hpp"
	// スレッド
	# include "Siv3D/Threading.hpp"
	// アロケータ
	# include "Siv3D/Allocator.hpp"
	// 動的配列
	# include "Siv3D/Array.hpp"
	// 範囲
	# include "Siv3D/Step.hpp"
	// 無限リスト
	# include "Siv3D/InfiniteList.hpp"
	// 二次元配列
	# include "Siv3D/Grid.hpp"
	// Optional
	# include "Siv3D/Optional.hpp"
	// unspecified
	# include "Siv3D/Unspecified.hpp"
	// 型特性
	# include "Siv3D/TypeTraits.hpp"
//
// 文字列と数値
//
	// 文字
	# include "Siv3D/Char.hpp"
	// 文字列
	# include "Siv3D/String.hpp"
	// 文字列ビュー
	# include "Siv3D/StringView.hpp"
	// 文字コード変換
	# include "Siv3D/CharacterSet.hpp"
	// 基数
	# include "Siv3D/Radix.hpp"
	// 大文字小文字
	# include "Siv3D/LetterCase.hpp"	
	// 数値
	# include "Siv3D/Number.hpp"
	// 多倍長整数
	# include "Siv3D/BigInt.hpp"
	// 多倍長浮動小数点数
	# include "Siv3D/BigFloat.hpp"
	// 整数のフォーマット
	# include "Siv3D/FormatInt.hpp"
	// 浮動小数点数のフォーマット
	# include "Siv3D/FormatFloat.hpp"
	// ブール値のフォーマット
	# include "Siv3D/FormatBool.hpp"
	// データ -> 文字列 の変換
	# include "Siv3D/Format.hpp"
	// フォーマットリテラル
	# include "Siv3D/FormatLiteral.hpp"
	// 文字列 -> 整数 の変換
	# include "Siv3D/ParseInt.hpp"
	// 文字列 -> 浮動小数点数 の変換
	# include "Siv3D/ParseFloat.hpp"
	// 文字列 -> ブール値 の変換
	# include "Siv3D/ParseBool.hpp"
	// 文字列 -> データ の変換
	# include "Siv3D/Parse.hpp"
	// 正規表現
	# include "Siv3D/Regex.hpp"
//
// 時刻と時間
//
	// 時間の単位
	# include "Siv3D/Duration.hpp"
	// 日付
	# include "Siv3D/Date.hpp"
	// 日付と時刻
	# include "Siv3D/DateTime.hpp"
	// 時間
	# include "Siv3D/Time.hpp"
	// ストップウォッチ
	# include "Siv3D/Stopwatch.hpp"
	// スピードを変更可能なストップウォッチ
	# include "Siv3D/SpeedStopwatch.hpp"
	// タイマー
	# include "Siv3D/Timer.hpp"
	// 処理にかかった時間の測定
	# include "Siv3D/TimeProfiler.hpp"
	// 処理にかかった CPU サイクル数の測定
	# include "Siv3D/RDTSCProfiler.hpp"
//
// ファイル I/O と暗号化
//
	// ファイルとディレクトリ
	# include "Siv3D/FileSystem.hpp"
	//// ファイルとディレクトリの変更の監視
	//# include "Siv3D/FileMonitor.hpp"
	// IReader インタフェース
	# include "Siv3D/IReader.hpp"
	// IWriter インタフェース
	# include "Siv3D/IWriter.hpp"
	//// 読み込み用バッファ
	//# include "Siv3D/ByteArray.hpp"
	//// 書き込み用バッファ
	//# include "Siv3D/MemoryWriter.hpp"
	// バイナリファイルの読み込み
	# include "Siv3D/BinaryReader.hpp"
	// バイナリファイルの書き込み
	# include "Siv3D/BinaryWriter.hpp"
	// テキストのエンコード
	# include "Siv3D/TextEncoding.hpp"
	//// テキストファイルの読み込み
	//# include "Siv3D/TextReader.hpp"
	// テキストファイルの書き込み
	# include "Siv3D/TextWriter.hpp"
	//// Base64
	//# include "Siv3D/Base64.hpp"
	//// MD5
	//# include "Siv3D/MD5.hpp"
	// ログファイル
	# include "Siv3D/Logger.hpp"
	//// AES128 による暗号化
	//# include "Siv3D/Crypto.hpp"
	//// Deflate によるデータの圧縮・展開
	//# include "Siv3D/Compression.hpp"
	//// アーカイブファイルからの読み込み
	//# include "Siv3D/ArchivedFileReader.hpp"
	//// アーカイブファイル
	//# include "Siv3D/FileArchive.hpp"
	//// CSV ファイルの読み込み
	//# include "Siv3D/CSVReader.hpp"
	//// CSV ファイルの書き出し
	//# include "Siv3D/CSVWriter.hpp"
	//// INI ファイルの読み込み
	//# include "Siv3D/INIReader.hpp"
	//// INI ファイルの書き出し
	//# include "Siv3D/INIWriter.hpp"
	//// XML ファイルの読み込み
	//# include "Siv3D/XMLReader.hpp"
	//// JSON ファイルの読み込み
	//# include "Siv3D/JSONReader.hpp"
	//// JSON ファイルの書き出し
	//# include "Siv3D/JSONWriter.hpp"
	//// ZIP 圧縮ファイルの読み込み
	//# include "Siv3D/ZIPReader.hpp"
	//// ZIP 圧縮ファイルの書き出し
	//# include "Siv3D/ZIPWriter.hpp"
//
// 色と二次元図形
//
	// RGB カラー
	# include "Siv3D/Color.hpp"
	// HSV カラー
	# include "Siv3D/HSV.hpp"
	// ベクトル
	# include "Siv3D/PointVector.hpp"
	// 円座標
	# include "Siv3D/Circular.hpp"
	//// 円柱座標
	//# include "Siv3D/Cylindrical.hpp"
	//// 球面座標
	//# include "Siv3D/Spherical.hpp"
	//// 3x2 行列
	//# include "Siv3D/Mat3x2.hpp"
	//// 線分
	//# include "Siv3D/Line.hpp"
	// 長方形
	# include "Siv3D/Rectangle.hpp"
	//// 円
	//# include "Siv3D/Circle.hpp"
	//// 楕円
	//# include "Siv3D/Ellipse.hpp"
	//// 三角形
	//# include "Siv3D/Triangle.hpp"
	//// 四角形
	//# include "Siv3D/Quad.hpp"
	//// 角丸長方形
	//# include "Siv3D/RoundRect.hpp"
	//// 連続した複数の線分
	//# include "Siv3D/LineString.hpp"
	//// 多角形
	//# include "Siv3D/Polygon.hpp"
	//// 多角形の集合
	//# include "Siv3D/MultiPolygon.hpp"
	//// 矢印形
	//# include "Siv3D/Arrow.hpp"
	//// 2D 図形の Variant
	//# include "Siv3D/Shape.hpp"
	//// レンダリング用形状
	//# include "Siv3D/FloatShape.hpp"
//
// 数学
//
	// 数学定数
	# include "Siv3D/MathConstants.hpp"
	// 乱数生成エンジン (Xorshift)
	# include "Siv3D/Xorshift.hpp"
	// 乱数生成エンジン (Mersenne Twister)
	# include "Siv3D/MersenneTwister.hpp"
	//// 乱数の分布
	//# include "Siv3D/Distribution.hpp"
	//// 乱数ユーティリティ
	//# include "Siv3D/Random.hpp"
	// 数学関数
	# include "Siv3D/Math.hpp"
	//// 線形補間
	//# include "Siv3D/Lerp.hpp"
	//// イージング関数
	//# include "Siv3D/Easing.hpp"
	//// イージング ユーティリティ
	//# include "Siv3D/EasingController.hpp"
	//// 2D 幾何
	//# include "Siv3D/Geometry2D.hpp"
	//// Perlin Noise
	//# include "Siv3D/PerlinNoise.hpp"
	//// スプライン
	//# include "Siv3D/Spline.hpp"
	//// 2 次ベジェ曲線
	//# include "Siv3D/QuadraticBezier.hpp"
	//// 3 次ベジェ曲線
	//# include "Siv3D/CubicBezier.hpp"
	//// SIMD
	//# include "Siv3D/SIMD.hpp"
	//// 半精度浮動小数点数
	//# include "Siv3D/HalfFloat.hpp"
	//// 数式パーサー
	//# include "Siv3D/ExpressionParser.hpp"
//
// 画像処理
//
	// 画像処理
	# include "Siv3D/Image.hpp"
	//// 画像のフォーマット
	//# include "Siv3D/TextureFormat.hpp"
	//// カスタムカラーフォーマット
	//# include "Siv3D/CustomColor.hpp"
	//// カスタムカラーフォーマットの画像
	//# include "Siv3D/CustomImage.hpp"
	//// QR コードの作成と認識
	//# include "Siv3D/QR.hpp"
	//// 手書き文字認識
	//# include "Siv3D/HandwritingRecognizer.hpp"
	//// 手書き文字認識用の学習データ作成
	//# include "Siv3D/HandwritingTrainer.hpp"
//
// 音声処理
//
	//// 音声波形のサンプル
	//# include "Siv3D/WaveSample.hpp"
	//// 音声波形
	//# include "Siv3D/Wave.hpp"
	//// 音声波形のテンポ・ピッチ変更
	//# include "Siv3D/WaveStretcher.hpp"
	//// FFT
	//# include "Siv3D/FFT.hpp"
//
// 動画ファイル
//
	//// GIF アニメーションの書き出し
	//# include "Siv3D/AnimatedGIFWriter.hpp"
	//// 動画ファイルの読み込み
	//# include "Siv3D/VideoReader.hpp"
	//// 動画ファイルの書き出し
	//# include "Siv3D/VideoWriter.hpp"
//
// ネットワーク・通信
//
	//// シリアル通信
	//# include "Siv3D/Serial.hpp"
	//// パイプサーバー
	//# include "Siv3D/PipeServer.hpp"
	//// インターネット
	//# include "Siv3D/Internet.hpp"
	//// HTTP
	//# include "Siv3D/HTTPClient.hpp"
	//// Twitter
	//# include "Siv3D/Twitter.hpp"
	//// ネットワーク
	//# include "Siv3D/Network.hpp"
	//// TCP サーバー
	//# include "Siv3D/TCPServer.hpp"
	//// TCP クライアント
	//# include "Siv3D/TCPClient.hpp"
//
// システム全般
//
	//// コマンドライン
	//# include "Siv3D/CommandLine.hpp"
	//// ユーザ固有 ID の取得
	//# include "Siv3D/UID.hpp"
	//// MIDI
	//# include "Siv3D/Midi.hpp"
	//// システム
	# include "Siv3D/System.hpp"
	//// ウィンドウ
	//# include "Siv3D/Window.hpp"
	//// メッセージボックス
	//# include "Siv3D/MessageBox.hpp"
	//// クリップボード
	//# include "Siv3D/Clipboard.hpp"
	//// ドラッグ & ドロップ
	//# include "Siv3D/Dragdrop.hpp"
	//// ダイアログ
	//# include "Siv3D/Dialog.hpp"
	//// プロファイリング
	//# include "Siv3D/Profiler.hpp"
//
// 入力デバイス
//
	//// マイク入力
	//# include "Siv3D/Recorder.hpp"
	//// キー入力
	//# include "Siv3D/Key.hpp"
	//// マウス
	//# include "Siv3D/Mouse.hpp"
	//// タッチ
	//# include "Siv3D/Touch.hpp"
	//// ペンタブレット
	//# include "Siv3D/Pentablet.hpp"
	//// ゲームパッド
	//# include "Siv3D/Gamepad.hpp"
	//// XInput 対応ゲームコントローラー
	//# include "Siv3D/XInput.hpp"
	//// 入力全般
	//# include "Siv3D/Input.hpp"
	//// Kinect V1
	//# include "Siv3D/KinectV1.hpp"
	//// Kinect V2
	//# include "Siv3D/KinectV2.hpp"
	//// Tobii EyeX
	//# include "Siv3D/TobiiEyeX.hpp"
//
// サウンド
//
	//// サウンド
	//# include "Siv3D/Sound.hpp"
	//// サウンドの拍カウント
	//# include "Siv3D/SoundBeat.hpp"
//
// グラフィックス
//
	//// ブレンドステート
	//# include "Siv3D/BlendState.hpp"
	//// ラスタライザーステート
	//# include "Siv3D/RasterizerState.hpp"
	//// デプスステートとステンシルステート
	//# include "Siv3D/DepthStencilState.hpp"
	//// サンプラーステート
	//# include "Siv3D/SamplerState.hpp"
	//// レンダーステート
	//# include "Siv3D/RenderState.hpp"
	//// シェーダ
	//# include "Siv3D/Shader.hpp"
	//// 頂点シェーダ
	//# include "Siv3D/VertexShader.hpp"
	//// ピクセルシェーダ
	//# include "Siv3D/PixelShader.hpp"
	//// 定数バッファ
	//# include "Siv3D/ConstantBuffer.hpp"
	//// 頂点レイアウト
	//# include "Siv3D/InputLayout.hpp"
	//// グラフィックス全般
	//# include "Siv3D/Graphics.hpp"
	//// スクリーンショット
	//# include "Siv3D/ScreenCapture.hpp"
	//// 2D グラフィックス設定
	//# include "Siv3D/Graphics2D.hpp"
	//// 2D スプライト
	//# include "Siv3D/Sprite.hpp"
//
// テクスチャ
//
	//// テクスチャ
	//# include "Siv3D/Texture.hpp"
	//// 領域を指定したテクスチャ
	//# include "Siv3D/TextureRegion.hpp"
	//// 四角形に貼り付けたテクスチャ
	//# include "Siv3D/TexturedQuad.hpp"
	//// 動的テクスチャ
	//# include "Siv3D/DynamicTexture.hpp"
	//// レンダーテクスチャ
	//# include "Siv3D/RenderTexture.hpp"
//
// フォント
//
	//// キネティックタイポグラフィ
	//# include "Siv3D/KineticTypography.hpp"
	//// フォント
	//# include "Siv3D/Font.hpp"
//
// 標準 GUI
//
	//// ウィジェットのスタイル
	//# include "Siv3D/WidgetStyle.hpp"
	//// IWidget インタフェース
	//# include "Siv3D/IWidget.hpp"
	//// テキストウィジェット
	//# include "Siv3D/GUIText.hpp"
	//// 改行ウィジェット
	//# include "Siv3D/GUINewLine.hpp"
	//// テクスチャウィジェット
	//# include "Siv3D/GUITexture.hpp"
	//// 水平線ウィジェット
	//# include "Siv3D/GUIHorizontalLine.hpp"
	//// ボタンウィジェット
	//# include "Siv3D/GUIButton.hpp"
	//// トグルスイッチウィジェット
	//# include "Siv3D/GUIToggleSwitch.hpp"
	//// 水平スライダーウィジェット
	//# include "Siv3D/GUISlider.hpp"
	//// チェックボックスウィジェット
	//# include "Siv3D/GUICheckBox.hpp"
	//// ラジオボタンウィジェット
	//# include "Siv3D/GUIRadioButton.hpp"
	//// テキスト入力フィールドウィジェット
	//# include "Siv3D/GUITextField.hpp"
	//// テキスト入力エリアウィジェット
	//# include "Siv3D/GUITextArea.hpp"
	//// カラーパレットウィジェット
	//# include "Siv3D/GUIColorPalette.hpp"
	//// GUI
	//# include "Siv3D/GUI.hpp"
	//// カーソル
	//# include "Siv3D/Cursor.hpp"
//
// ムービー
//
	//// ムービー (AVI, WMV 等に対応)
	//# include "Siv3D/VideoPlayer.hpp"
	//// メディアプレイヤー (AVI, WMV, MP4 等に対応)
	//# include "Siv3D/MediaPlayer.hpp"
//
// Web カメラと AR
//
	//// Web カメラ
	//# include "Siv3D/Webcam.hpp"
	//// AR マーカー
	//# include "Siv3D/AR.hpp"
//
// 3D 幾何
//
	//// DirectXMath ユーティリティ
	//# include "Siv3D/DirectXMathUtility.hpp"
	//// クォータニオン
	//# include "Siv3D/Quaternion.hpp"
	//// 4x4 行列
	//# include "Siv3D/Mat4x4.hpp"
	//// レイ
	//# include "Siv3D/Ray.hpp"
	//// 3D 線分
	//# include "Siv3D/Line3D.hpp"
	//// 3D 三角形
	//# include "Siv3D/Triangle3D.hpp"
	//// メッシュデータ
	//# include "Siv3D/MeshData.hpp"
	//// メッシュ
	//# include "Siv3D/Mesh.hpp"
	//// 動的メッシュ
	//# include "Siv3D/DynamicMesh.hpp"
	//// 変換情報を持ったメッシュ
	//# include "Siv3D/TransformedMesh.hpp"
	//// パーティクル
	//# include "Siv3D/Particle.hpp"
	//// 平面
	//# include "Siv3D/Plane.hpp"
	//// 球
	//# include "Siv3D/Sphere.hpp"
	//// ボックス
	//# include "Siv3D/Box.hpp"
	//// 円盤
	//# include "Siv3D/Disc.hpp"
	//// 円柱
	//# include "Siv3D/Cylinder.hpp"
	//// 円錐
	//# include "Siv3D/Cone.hpp"
	//// 3D 幾何
	//# include "Siv3D/Geometry3D.hpp"
	//// OBJ ファイル読み込み
	//# include "Siv3D/ModelLoader.hpp"
	//// 3D モデル
	//# include "Siv3D/Model.hpp"
	//// 3D カメラ
	//# include "Siv3D/Camera.hpp"
	//// フォグ
	//# include "Siv3D/Fog.hpp"
	//// ライト
	//# include "Siv3D/Light.hpp"
	//// 3D グラフィックス設定
	//# include "Siv3D/Graphics3D.hpp"
	//// ポストエフェクト
	//# include "Siv3D/PostEffect.hpp"
//
// アセット
//
	//// アセット管理
	//# include "Siv3D/Asset.hpp"
	//// Sound アセット
	//# include "Siv3D/SoundAsset.hpp"
	//// Texture アセット
	//# include "Siv3D/TextureAsset.hpp"
	//// Font アセット
	//# include "Siv3D/FontAsset.hpp"
	//// GUI アセット
	//# include "Siv3D/GUIAsset.hpp"
//
// ユーティリティ
//
	//// エフェクト
	//# include "Siv3D/Effect.hpp"
	//// コンソールウィンドウ
	//# include "Siv3D/Console.hpp"
	//// デバッグ出力
	//# include "Siv3D/ApplicationUtility.hpp"
	//// アドオン
	//# include "Siv3D/Addon.hpp"
	//// マルチスレッド
	//# include "Siv3D/Threading.hpp"
	//// シリアライゼーション
	//# include "Siv3D/Serialization.hpp"
	//// 名前空間の設定
	//# include "Siv3D/Namespace.hpp"
	//// GPU の使用
	//# include "Siv3D/HighPerfoemanceGraphics.hpp"
