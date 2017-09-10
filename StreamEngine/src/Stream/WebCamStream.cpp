#include "WebCamStream.h"

using namespace cv;

CWebCamStream::CWebCamStream(int iWebCamDeviceID)
    : QThread()
    , CStreamClient()
    , m_bQuitThread(false)
    , m_iWebCamDeviceID(iWebCamDeviceID)
    , m_dFps(20)
{
}

CWebCamStream::~CWebCamStream()
{
    Stop();
}

void CWebCamStream::Play()
{
    m_vCap.open(m_iWebCamDeviceID);
    StartThread();
}

void CWebCamStream::Pause()
{
    Stop();
}

void CWebCamStream::Stop()
{
    StopThread();
    m_vCap.release();
}

void CWebCamStream::run()
{
    while (!m_bQuitThread)
    {
        if (m_CbDecodeVideo && m_vCap.isOpened())
        {
            Mat cvframe;
            m_vCap.read(cvframe);

            CImageAdaptor frame(cvframe);
            m_CbDecodeVideo(m_pListener, frame);
            msleep(1000 / m_dFps);
        }
        
    }
}

void CWebCamStream::StartThread()
{
    if (!isRunning())
    {
        m_bQuitThread = false;
        start();
    }
}

void CWebCamStream::StopThread()
{
    m_bQuitThread = true;

    while (isRunning())
    {
        wait(100);
    }
}

void CWebCamStream::SetFPS(double fps)
{
    m_dFps = fps;
}
