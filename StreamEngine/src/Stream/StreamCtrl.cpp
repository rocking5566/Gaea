#include "StreamCtrl.h"
#include "RtspStream.h"
#include "WebCamStream.h"
#include "Util.h"

CStreamCtrl::CStreamCtrl(int streamID, QObject* parent /*= NULL*/)
    : QThread(parent)
    , m_iStreamID(streamID)
    , m_pStreamClient(NULL)
    , m_SessionType(eNone)
    , m_bQuit(false)
{
    StartDeliverThread();
}

CStreamCtrl::~CStreamCtrl()
{
    StopDeliverThread();
    DisConnect();
}

int CStreamCtrl::GetStreamID()
{
    return m_iStreamID;
}

bool CStreamCtrl::Connect(const SConnectInfo& rInfo)
{
    bool ret = false;

    if (m_SessionType == eNone)
    {
        m_SessionType = rInfo.m_type;

        switch (rInfo.m_type)
        {
        case eRTSP:
            if (!rInfo.m_sUrl.isEmpty())
            {
                m_pStreamClient = new CRtspStream();
                m_pStreamClient->RegisterDecodeVideoCallback(VideoDecodeCallback, this);
                m_pStreamClient->SetUrl(rInfo.m_sUrl.toStdString().c_str());
                m_pStreamClient->Play();

                ret = true;
            }
            break;
        case eWebCam:
            m_pStreamClient = new CWebCamStream(rInfo.m_iWebCamDeviceID);
            m_pStreamClient->RegisterDecodeVideoCallback(VideoDecodeCallback, this);
            m_pStreamClient->Play();
            break;
        default:
            break;
        }
    }

    return ret;
}

void CStreamCtrl::DisConnect()
{
    switch (m_SessionType)
    {
    case eRTSP:
    case eWebCam:
        if (m_pStreamClient)
        {
            m_pStreamClient->Stop();
            m_pStreamClient->UnRegisterDecodeVideoCallback();
            SAFE_DELETE(m_pStreamClient);
        }
        break;

    default:
        break;
    }

    m_SessionType = eNone;
}

void CStreamCtrl::VideoDecodeCallback(void* _this, CImageAdaptor frame)
{
    // TODO - Congestion control

    CStreamCtrl* This = (CStreamCtrl*)_this;
    This->m_DecodeImgQueueMutex.lock();
    This->m_DecodeImgQueue.push_back(frame);
    This->m_WorkingCondition.wakeOne();
    This->m_DecodeImgQueueMutex.unlock();
}

void CStreamCtrl::run()
{
    while (!m_bQuit)
    {
        {
            QMutexLocker locker(&m_DecodeImgQueueMutex);
            while (!m_bQuit && m_DecodeImgQueue.empty())
            {
                m_WorkingCondition.wait(&m_DecodeImgQueueMutex);
            }
        }

        m_DecodeImgQueueMutex.lock();
        m_DeliveringDecodeImgQueue = m_DecodeImgQueue;
        m_DecodeImgQueue.clear();
        m_DecodeImgQueueMutex.unlock();

        while (!m_DeliveringDecodeImgQueue.empty() && !m_bQuit)
        {
            DeliverVideo();
        }
    }
}

void CStreamCtrl::DeliverVideo()
{
    CImageAdaptor frame = m_DeliveringDecodeImgQueue.front();

    for (auto iter = m_listenerCallbackList.begin(); iter != m_listenerCallbackList.end(); ++iter)
    {
        // StreamCb
        iter->second(iter->first, this, frame);
    }

    m_DeliveringDecodeImgQueue.pop_front();
}

void CStreamCtrl::StartDeliverThread()
{
    if (!isRunning())
    {
        m_bQuit = false;
        start();
    }
}

void CStreamCtrl::StopDeliverThread()
{
    m_bQuit = true;
    m_WorkingCondition.wakeOne();

    while (isRunning())
    {
        wait(100);
    }
}

void CStreamCtrl::Attach(StreamCb videoCb, void* pListener)
{
    m_listenerCallbackList << qMakePair(pListener, videoCb);
}

void CStreamCtrl::Detach(void* pListener)
{
    for (auto iter = m_listenerCallbackList.begin(); iter != m_listenerCallbackList.end(); ++iter)
    {
        if(iter->first == pListener)
        {
            m_listenerCallbackList.erase(iter);
            break;
        }
    }
}
