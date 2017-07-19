#ifndef StreamSession_h__
#define StreamSession_h__

#include <QThread>

class CStreamSession : public QThread
{
    Q_OBJECT

public:
    CStreamSession(QObject* parent = NULL);
    ~CStreamSession();
};
#endif // StreamSession_h__