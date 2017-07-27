#ifndef StreamSession_h__
#define StreamSession_h__

#include <QThread>
#include <QWaitCondition>
#include "def/KernelTypes.h"
#include "VideoFrame.h"

class CRtspStream;

/*!
    This class responsible for congestion control, error handle for the stream.
    Compatible with many types of stream.
    Ex: RTSP, web cam, local file ... etc.
*/
class CStreamCtrl : public QThread
{
    Q_OBJECT

public:
    CStreamCtrl(QObject* parent = NULL);
    ~CStreamCtrl();

    bool Connect(const SConnectInfo& rInfo); // blocking API
    void DisConnect();

private:
    static void VideoDecodeCallback(void* context, CVideoFrame frame);
    void DeliverData();

    virtual void run();
    void StartDeliverThread();
    void StopDeliverThread();

private:
    bool m_bQuit;
    QMutex m_DecodeImgQueueMutex;
    QWaitCondition m_WorkingCondition;


    CRtspStream* m_pRtspStream;
    EConnectType m_SessionType;
    QList<CVideoFrame> m_DecodeImgQueue;
};
#endif // StreamSession_h__