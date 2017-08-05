#include "PlayerCtrl.h"
#include "StreamCtrl.h"
#include "util/Util.h"

#define RequestType_Connect 1
#define RequestType_DisConnect 2

CPlayerCtrl::CPlayerCtrl(QObject* parent)
    : CWorkerThread(parent)
    , m_iStreamNextID(0)
{

}

CPlayerCtrl::~CPlayerCtrl()
{
    auto iter = m_mapIdToStreamData.constBegin();
    while (iter != m_mapIdToStreamData.constEnd())
    {
        iter.value().m_Stream->DisConnect();
        ++iter;
    }
}

void CPlayerCtrl::AttachStream(int iStreamID, VideoCb videoCb, void* pListener)
{
    if (m_mapIdToStreamData.contains(iStreamID))
    {
        SStreamCallbackData cbData;
        cbData.m_cb = videoCb;
        cbData.m_pListener = pListener;

        m_mapIdToStreamData[iStreamID].m_callbackList << cbData;
    }
}

void CPlayerCtrl::DetachStream(int iStreamID, void* pListener)
{
    if (m_mapIdToStreamData.contains(iStreamID))
    {
        SPlayerStreamData& rStreamData = m_mapIdToStreamData[iStreamID];

        for (auto iter = rStreamData.m_callbackList.begin(); iter != rStreamData.m_callbackList.end(); ++iter)
        {
            if (iter->m_pListener == pListener)
            {
                rStreamData.m_callbackList.erase(iter);
                break;
            }
        }

    }
}

void CPlayerCtrl::StreamCallback(void *_this, CStreamCtrl* pSrcStream, CVideoFrame frame)
{
    CPlayerCtrl* This = (CPlayerCtrl*)_this;
    int streamID = pSrcStream->GetStreamID();

    if (This->m_mapIdToStreamData.contains(streamID))
    {
        const QList<SStreamCallbackData>& rCallbackList = This->m_mapIdToStreamData[streamID].m_callbackList;
        foreach (SStreamCallbackData cbData, rCallbackList)
        {
            cbData.m_cb(cbData.m_pListener, streamID, frame);
        }
    }
    else
    {
        // TODO - error handle
        // detach stream
    }
}

void CPlayerCtrl::HandleRequest(SRequest request)
{
    switch (request.m_RequestType)
    {
    case RequestType_None:
        break;
    case RequestType_Connect:
        OnConnect(request.m_Param1.toInt());
        break;
    case RequestType_DisConnect:
        DisConnect(request.m_Param1.toInt(), false);
    default:
        break;
    }
}

int CPlayerCtrl::Connect(const SConnectInfo& rInfo)
{
    m_StreamsLock.lockForWrite();

    int iStreamID = m_iStreamNextID++;
    SPlayerStreamData streamData;
    streamData.m_StreamInfo = rInfo;
    streamData.m_Stream = new CStreamCtrl(iStreamID);
    m_mapIdToStreamData[iStreamID] = streamData;
    PushRequestToQueue(RequestType_Connect, iStreamID, NULL);

    m_StreamsLock.unlock();

    return iStreamID;
}

void CPlayerCtrl::OnConnect(int iStreamID)
{
    SPlayerStreamData& rStreamData = m_mapIdToStreamData[iStreamID];
    rStreamData.m_Stream->Connect(rStreamData.m_StreamInfo);
    rStreamData.m_Stream->Attach(StreamCallback, this);
}

void CPlayerCtrl::DisConnect(int iStreamID, bool bIsAsync)
{
    if (bIsAsync)
    {
        PushRequestToQueue(RequestType_DisConnect, iStreamID, NULL);
    }
    else
    {
        if (m_mapIdToStreamData.contains(iStreamID))
        {
            m_mapIdToStreamData[iStreamID].m_Stream->Detach(this);
            m_mapIdToStreamData[iStreamID].m_Stream->DisConnect();
            SAFE_DELETE(m_mapIdToStreamData[iStreamID].m_Stream);
            m_mapIdToStreamData.remove(iStreamID);
        }
    }
}
