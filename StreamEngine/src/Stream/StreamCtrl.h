#ifndef StreamSession_h__
#define StreamSession_h__

#include <QThread>
#include <QWaitCondition>
#include <QMap>
#include <QMutex>
#include "StreamEngineTypes.h"
#include "ImageAdaptor.h"

class CStreamClient;
class CStreamCtrl;
typedef void (*StreamCb)(void *pListener, CStreamCtrl* pSrcStream, CImageAdaptor frame);

/*!
    This class responsible for congestion control, error handle for the stream.
    Compatible with many types of stream.
    Ex: RTSP, web cam, local file ... etc.
*/
class CStreamCtrl : public QThread
{
    Q_OBJECT

public:
    CStreamCtrl(int streamID, QObject* parent = NULL);
    ~CStreamCtrl();

    int GetStreamID();
    bool Connect(const SConnectInfo& rInfo); // blocking API
    void DisConnect();
    void Attach(StreamCb videoCb, void* pListener);
    void Detach(void* pListener);

private:
    static void VideoDecodeCallback(void* _this, CImageAdaptor frame);
    void DeliverVideo();

    virtual void run();
    void StartDeliverThread();
    void StopDeliverThread();

private:
    bool m_bQuit;
    QMutex m_DecodeImgQueueMutex;
    QWaitCondition m_WorkingCondition;

    int m_iStreamID;
    CStreamClient* m_pStreamClient;
    EConnectType m_SessionType;
    QList<CImageAdaptor> m_DecodeImgQueue;
    QList<CImageAdaptor> m_DeliveringDecodeImgQueue;
    QList<QPair<void*, StreamCb> > m_listenerCallbackList;
};
#endif // StreamSession_h__
