#ifndef PlayerCtrl_h__
#define PlayerCtrl_h__

#include "util/WorkerThread.h"

class CPlayCtrl : public CWorkerThread
{
    Q_OBJECT

public:
    CPlayCtrl(QObject* parent = NULL);
    ~CPlayCtrl();
};
#endif // PlayerCtrl_h__