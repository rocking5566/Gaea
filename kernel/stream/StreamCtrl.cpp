#include "StreamCtrl.h"
#include "RtspStream.h"
#include "util/Util.h"

CStreamCtrl::CStreamCtrl(QObject* parent /*= NULL*/)
    : QThread(parent)
    , m_pRtspStream(NULL)
    , m_SessionType(eNone)
{

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

void CStreamCtrl::VideoDecodeCallback(void* context, void* frame)
{
    // TODO - deliver thread
    int i = 0;
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

