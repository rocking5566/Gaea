#include "TabEntity.h"
#include "ui_LiveViewWidget.h"
#include "PlayerCtrl.h"
#include "VideoFrame.h"

class CLiveViewWidget : public CTabEntity
{
    Q_OBJECT

public:
    explicit CLiveViewWidget(QWidget *parent = 0);
    ~CLiveViewWidget();

    // override CTabEntity
    virtual void Enter();
    virtual void Leave();

private slots:
    void OnTreeWidgetSelectionChanged();

private:
    void ConnectUISignal();
    void InitDeviceTree();

    static void playerCallback(void *_this, int id, CVideoFrame frame);

private:
    Ui::LiveViewWidget m_ui;
    CPlayerCtrl m_pPlayerCtrl;
    int m_curStreamId;
};
