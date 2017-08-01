#ifndef PlayerCtrl_h__
#define PlayerCtrl_h__

#include <QReadWriteLock>
#include "util/WorkerThread.h"
#include "def/KernelTypes.h"
#include "VideoFrame.h"

class CStreamCtrl;
typedef void(*VideoCb)(void *pListener, int streamId, CVideoFrame frame);

/*!
    This class provide interfaces to play multiple streams simultaneously.
*/
class CPlayerCtrl : public CWorkerThread
{
    Q_OBJECT

public:
    CPlayerCtrl(QObject* parent = NULL);
    ~CPlayerCtrl();

    void AttachStream(int iStreamID, VideoCb videoCb, void* pListener);
    void DetachStream(int iStreamID, void* pListener);

    int Connect(const SConnectInfo& rInfo);     // non-blocking API
    void DisConnect(int iStreamIndex, bool bIsAsync);

private:
    static void StreamCallback(void *_this, CStreamCtrl* pSrcStream, CVideoFrame frame);

    // override CWorkerThread
    virtual void HandleRequest(SRequest request);

    void OnConnect(int iStreamID);

    struct SStreamCallbackData
    {
        SStreamCallbackData()
            : m_cb(NULL)
            , m_pListener(NULL)
        {
        };
        VideoCb m_cb;
        void* m_pListener;
    };

    struct SPlayerStreamData
    {
        SPlayerStreamData()
            : m_Stream(NULL)
        {
        };
        SConnectInfo m_StreamInfo;
        CStreamCtrl* m_Stream;
        QList<SStreamCallbackData> m_callbackList;
    };

private:
    QReadWriteLock m_StreamsLock;
    int m_iStreamNextID;
    QMap<int, SPlayerStreamData> m_mapIdToStreamData;   //ID -> SPlayerStreamData
};
#endif // PlayerCtrl_h__