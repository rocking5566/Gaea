#ifndef StreamSession_h__
#define StreamSession_h__

#include <QThread>
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

private:
    CRtspStream* m_pRtspStream;
    EConnectType m_SessionType;
};
#endif // StreamSession_h__