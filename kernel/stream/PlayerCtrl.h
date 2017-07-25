#ifndef PlayerCtrl_h__
#define PlayerCtrl_h__

#include "util/WorkerThread.h"

/*!
    This class provide interfaces to play multiple streams simultaneously.
*/
class CPlayCtrl : public CWorkerThread
{
    Q_OBJECT

public:
    CPlayCtrl(QObject* parent = NULL);
    ~CPlayCtrl();
};
#endif // PlayerCtrl_h__