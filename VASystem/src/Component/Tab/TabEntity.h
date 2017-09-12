#ifndef TabEntity_h__
#define TabEntity_h__

#include <QWidget>

class CTabEntity : public QWidget
{
    Q_OBJECT

public:
    explicit CTabEntity(QWidget *parent = 0);
    ~CTabEntity();

    virtual void Enter() = 0;
    virtual void Leave() = 0;

};
#endif // TabEntity_h__
