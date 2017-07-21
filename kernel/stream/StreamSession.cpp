#include "StreamSession.h"
#include "RtspHelper.h"
#include "util/Util.h"

CStreamSession::CStreamSession(QObject* parent /*= NULL*/)
    : QThread(parent)
    , m_pRtspHelper(NULL)
    , m_SessionType(eNone)
{

}

CStreamSession::~CStreamSession()
{
    SAFE_DELETE(m_pRtspHelper);
}

bool CStreamSession::Connect(SConnectInfo info)
{
    bool ret = false;

    if (m_SessionType == eNone)
    {
        switch (info.m_type)
        {
        case eRTSP:
            if (!info.m_sUrl.isEmpty())
            {
                m_SessionType = info.m_type;
                m_pRtspHelper = new CRtspHelper();
                m_pRtspHelper->RegisterDecodeVideoCallback(VideoDecodeCallback, this);
                m_pRtspHelper->SetUrl(info.m_sUrl.toStdString().c_str());
                m_pRtspHelper->Play();

                ret = true;
            }
            break;

        default:
            break;
        }
    }

    return ret;
}

void CStreamSession::VideoDecodeCallback(void* context, void* frame)
{
    // TODO - deliver thread
}

void CStreamSession::DisConnect()
{
    switch (m_SessionType)
    {
    case eRTSP:
        m_pRtspHelper->Stop();
        break;

    default:
        break;
    }
}

