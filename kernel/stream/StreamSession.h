#ifndef StreamSession_h__
#define StreamSession_h__

#include <QThread>
#include "def/KernelTypes.h"

class CRtspHelper;

class CStreamSession : public QThread
{
    Q_OBJECT

public:
    CStreamSession(QObject* parent = NULL);
    ~CStreamSession();

    bool Connect(SConnectInfo info); // blocking API
    void DisConnect();

private:
    static void VideoDecodeCallback(void* context, void* frame);

private:
    CRtspHelper* m_pRtspHelper;
    EConnectType m_SessionType;
};
#endif // StreamSession_h__