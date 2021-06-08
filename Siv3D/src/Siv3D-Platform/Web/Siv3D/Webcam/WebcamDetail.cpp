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

# include <Siv3D/System.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Texture/GLES3/CTexture_GLES3.hpp>
# include "WebcamDetail.hpp"

namespace s3d
{

	Webcam::WebcamDetail::WebcamDetail() 
	{
		::glGenFramebuffers(1, &m_copyFrameBuffer);
		m_frameBufferUnpackers.resize(2);
	}

	Webcam::WebcamDetail::~WebcamDetail()
	{
		close();
		::glDeleteFramebuffers(1, &m_copyFrameBuffer);
	}

	bool Webcam::WebcamDetail::open(const uint32 cameraIndex)
	{
		LOG_SCOPED_TRACE(U"Webcam::WebcamDetail::open(cameraIndex = {})"_fmt(cameraIndex));

		// close();

		m_abort = false;

		// TODO: カメラのデフォルトの解像度も取得したい
		m_capture.setResolution(m_captureResolution);

		if (not m_capture.openCamera())
		{
			LOG_ERROR(U"cv::VideoCapture::open({}) failed"_fmt(cameraIndex));
			
			return false;
		}

		LOG_INFO(U"cv::VideoCapture::open({}) succeeded"_fmt(cameraIndex));

		m_cameraIndex = cameraIndex;

		return true;
	}

	void Webcam::WebcamDetail::close()
	{
		if (not m_capture.isOpened())
		{
			return;
		}

		if (not m_thread.joinable())
		{
			return;
		}

		m_abort = true;

		m_thread.join();
		{
			m_capture.release();
			m_cameraIndex = 0;
			m_newFrameCount = 0;
			// m_captureResolution.set(0, 0);
		}
	}

	bool Webcam::WebcamDetail::isOpen()
	{
		return m_capture.isOpened();
	}

	bool Webcam::WebcamDetail::start()
	{
		// すでに start 後の場合は何もしない
		if (m_thread.joinable())
		{
			return true;
		}

		// キャプチャスレッドを起動
		{
			m_thread = PseudoThread{ std::chrono::milliseconds(30), Run, std::ref(*this) };

			for (auto& unpacker : m_frameBufferUnpackers)
			{
				unpacker.resize(m_captureResolution);
			}

			return true;
		}
	}

	bool Webcam::WebcamDetail::isActive() const
	{
		return m_thread.joinable();
	}

	uint32 Webcam::WebcamDetail::cameraIndex() const
	{
		return m_cameraIndex;
	}

	Size Webcam::WebcamDetail::getResolution() const
	{
		return m_captureResolution;
	}

	bool Webcam::WebcamDetail::setResolution(const Size& resolution)
	{
		// BUGBUG: Web 版では open 前でなければ解像度変更ができない
		if (m_capture.isOpened())
		{
			return false;
		}

		// start 後は変更できない
		if (m_thread.joinable())
		{
			return false;
		}

		m_captureResolution = resolution;

		return true;
	}

	bool Webcam::WebcamDetail::hasNewFrame()
	{
		return (0 < m_newFrameCount);
	}

	bool Webcam::WebcamDetail::getFrame(Image& image)
	{
		if (not isActive())
		{
			return false;
		}

		auto& selectedUnpacker = m_frameBufferUnpackers[m_totalFrameCount % 2];

		if (!selectedUnpacker.hasFinishedUnpack())
		{
			return false;
		}

		image.resize(m_captureResolution);
		{
			selectedUnpacker.readPixels(image);

			m_newFrameCount = 0;
		}

		return true;
	}

	bool Webcam::WebcamDetail::getFrame(DynamicTexture& texture)
	{
		if (not isActive())
		{
			return false;
		}

		auto textureManager = static_cast<CTexture_GLES3*>(Siv3DEngine::Get<ISiv3DTexture>());

		{
			::glBindFramebuffer(GL_READ_FRAMEBUFFER, m_capturedFrameBuffer);
			::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_copyFrameBuffer);
			::glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureManager->getTexture(texture.id()), 0);
			
			::glBlitFramebuffer(
				0, 0, m_captureResolution.x, m_captureResolution.y,
				0, 0, texture.width(), texture.height(),
				GL_COLOR_BUFFER_BIT, GL_NEAREST
			);

			::glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);

			::glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
			::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		}

		m_newFrameCount = 0;

		return true;
	}
	
	bool Webcam::WebcamDetail::Run(WebcamDetail& webcam)
	{
		auto& capture = webcam.m_capture;

		if (webcam.m_abort)
		{
			// false を返して疑似スレッド終了
			return false;
		}

		if (not capture.isOpened())
		{
			// isOpen != true でなくても start できる代わりに、
			// ここで open チェック
			return true;
		}

		capture.capture();
		auto capturedFrameBuffer = capture.retrieve();
		auto& selectedUnpacker = webcam.m_frameBufferUnpackers[webcam.m_totalFrameCount % 2];

		selectedUnpacker.startUnpack(capturedFrameBuffer);

		webcam.m_capturedFrameBuffer = capturedFrameBuffer;
		webcam.m_newFrameCount++;
		webcam.m_totalFrameCount++;

		return true;
	}
}
