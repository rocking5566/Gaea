#include "TabEntity.h"
#include "ui_LiveViewWidget.h"

class CLiveViewWidget : public CTabEntity
{
    Q_OBJECT

public:
    explicit CLiveViewWidget(QWidget *parent = 0);
    ~CLiveViewWidget();

    // override CTabEntity
    virtual void Enter();
    virtual void Leave();

private:
    void InitDeviceTree();

private:
    Ui::LiveViewWidget m_ui;
};
