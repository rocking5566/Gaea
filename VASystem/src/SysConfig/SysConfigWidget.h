#ifndef SysConfigWidget_h__
#define SysConfigWidget_h__

#include "Tab/TabEntity.h"
#include "ui_SysConfigWidget.h"

class CSysConfigWidget : public CTabEntity
{
    Q_OBJECT

public:
    explicit CSysConfigWidget(QWidget *parent = 0);
    ~CSysConfigWidget();

    // override CTabEntity
    virtual void Enter();
    virtual void Leave();

private slots:
    void OnBtnClearAllSysDataClicked();

private:
    void ConnectUISignal();

private:
    Ui::SysConfigWidget m_ui;
    int x;
};
#endif // SysConfigWidget_h__
