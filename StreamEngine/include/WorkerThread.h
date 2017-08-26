#ifndef WorkerThread_h__
#define WorkerThread_h__

#include <QThread>
#include <QVariant>
#include <QMutex>
#include <QWaitCondition>
#include <QWaitCondition>
#include <list>

#define RequestType_None 0
typedef int RequestType;

struct SRequest
{
    int m_RequestType;
    QVariant m_Param1;
    void *m_pvParam2;

    SRequest()
    {
        m_RequestType = RequestType_None;
        m_Param1 = 0;
        m_pvParam2 = NULL;
    }
};

/*!
    This class implement the worker-thread pattern.
    Just inherit me!
*/
class CWorkerThread : public QThread
{
    Q_OBJECT

public:
    CWorkerThread(QObject* parent = NULL);
    virtual ~CWorkerThread();

protected:
    void Start();
    void Stop();
    void PushRequestToQueue(RequestType type, QVariant iParam1, void *pvParam2);

    virtual void HandleRequest(SRequest request) = 0;

private:
    virtual void run();

private:
    bool m_bQuit;
    QMutex m_RequestsMutex;
    QWaitCondition m_WorkingCondition;
    std::list<SRequest> m_Requests;
    std::list<SRequest> m_HandlingRequests;
};
#endif // WorkerThread_h__