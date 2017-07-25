#ifndef StreamSession_h__
#define StreamSession_h__

#include <QThread>
#include <QWaitCondition>
#include "def/KernelTypes.h"

class CRtspStream;

class CStreamCtrl : public QThread
{
    Q_OBJECT

public:
    CStreamCtrl(QObject* parent = NULL);
    ~CStreamCtrl();

    bool Connect(const SConnectInfo& rInfo); // blocking API
    void DisConnect();

private:
    static void VideoDecodeCallback(void* context, void* frame);

    void run();
    void Start();
    void Stop();

private:
    bool m_bQuit;
    QMutex m_DecodeImgQueueMutex;
    QWaitCondition m_WorkingCondition;


    CRtspStream* m_pRtspStream;
    EConnectType m_SessionType;
    QList<uchar*> m_DecodeImgQueue;
};
#endif // StreamSession_h__