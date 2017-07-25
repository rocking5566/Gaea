#include "StreamCtrl.h"
#include "RtspStream.h"
#include "util/Util.h"

CStreamCtrl::CStreamCtrl(QObject* parent /*= NULL*/)
    : QThread(parent)
    , m_pRtspStream(NULL)
    , m_SessionType(eNone)
    , m_bQuit(false)
{
    Start();
}

CStreamCtrl::~CStreamCtrl()
{
    DisConnect();
}

bool CStreamCtrl::Connect(const SConnectInfo& rInfo)
{
    bool ret = false;

    if (m_SessionType == eNone)
    {
        switch (rInfo.m_type)
        {
        case eRTSP:
            if (!rInfo.m_sUrl.isEmpty())
            {
                m_SessionType = rInfo.m_type;
                m_pRtspStream = new CRtspStream();
                m_pRtspStream->RegisterDecodeVideoCallback(VideoDecodeCallback, this);
                m_pRtspStream->SetUrl(rInfo.m_sUrl.toStdString().c_str());
                m_pRtspStream->Play();

                ret = true;
            }
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
        m_pRtspStream->Stop();
        m_pRtspStream->UnRegisterDecodeVideoCallback();
        SAFE_DELETE(m_pRtspStream);
        break;

    default:
        break;
    }

    m_SessionType = eNone;
}

void CStreamCtrl::VideoDecodeCallback(void* context, CVideoFrame frame)
{
    // TODO - Congestion control

    CStreamCtrl* This = (CStreamCtrl*)context;
    This->m_DecodeImgQueueMutex.lock();
    This->m_DecodeImgQueue.push_back(frame);
    This->m_WorkingCondition.wakeOne();
    This->m_DecodeImgQueueMutex.unlock();
}

void CStreamCtrl::run()
{
    while (!m_bQuit)
    {
        QMutexLocker locker(&m_DecodeImgQueueMutex);
        while (!m_bQuit && m_DecodeImgQueue.empty())
        {
            m_WorkingCondition.wait(&m_DecodeImgQueueMutex);
        }

        // TODO - Deliver data to callback
        CVideoFrame frame = m_DecodeImgQueue.front();

        m_DecodeImgQueue.pop_front();
    }
}

void CStreamCtrl::Start()
{
    if (!isRunning())
    {
        m_bQuit = false;
        start();
    }
}

void CStreamCtrl::Stop()
{
    m_bQuit = true;
    m_WorkingCondition.wakeOne();
}

