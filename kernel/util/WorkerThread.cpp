#include "WorkerThread.h"

CWorkerThread::CWorkerThread(QObject* parent)
    : QThread(parent)
    , m_bQuit(false)
{
    Start();
}

CWorkerThread::~CWorkerThread()
{
    m_bQuit = true;
    m_WorkingCondition.wakeOne();

    while (isRunning())
    {
        wait(100);
    }
}

void CWorkerThread::run()
{
    while (!m_bQuit)
    {
        {
            // Go to sleep if there's nothing to do.
            QMutexLocker locker(&m_RequestsMutex);
            while (!m_bQuit && m_Requests.empty())
            {
                m_WorkingCondition.wait(&m_RequestsMutex);
            }
        }

        // Process pending requests
        m_RequestsMutex.lock();
        m_HandlingRequests = m_Requests;
        m_Requests.clear();
        m_RequestsMutex.unlock();

        while ((!m_HandlingRequests.empty()) && (!m_bQuit))
        {
            SRequest request = m_HandlingRequests.front();
            m_HandlingRequests.pop_front();
            HandleRequest(request);
        }
    }
}

void CWorkerThread::Start()
{
    if (!isRunning())
    {
        m_bQuit = false;
        start();
    }
}

void CWorkerThread::Stop()
{
    m_bQuit = true;
    m_WorkingCondition.wakeOne();
}

void CWorkerThread::PushRequestToQueue(RequestType type, QVariant iParam1, void *pvParam2)
{
    SRequest request;
    request.m_RequestType = type;
    request.m_Param1 = iParam1;
    request.m_pvParam2 = pvParam2;

    m_RequestsMutex.lock();
    m_Requests.push_back(request);
    m_WorkingCondition.wakeOne();
    m_RequestsMutex.unlock();
}

