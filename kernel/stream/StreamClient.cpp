#include "StreamClient.h"

CStreamClient::CStreamClient()
    : m_CbDecodeVideo(NULL)
    , m_pListener(NULL)
{
    memset(&m_profile, 0, sizeof(SVideoProfile));
}

CStreamClient::~CStreamClient()
{

}

void CStreamClient::RegisterDecodeVideoCallback(DecodeVideoCb videoCb, void* pListener)
{
    m_CbDecodeVideo = videoCb;
    m_pListener = pListener;
}

void CStreamClient::UnRegisterDecodeVideoCallback()
{
    m_CbDecodeVideo = NULL;
    m_pListener = NULL;
}
