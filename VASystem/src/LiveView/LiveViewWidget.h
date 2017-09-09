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
    void OnCurrentItemChanged(QTreeWidgetItem *pCurrent, QTreeWidgetItem *pPrevious);

private:
    void ConnectUISignal();
    void SetupDeviceTree();
    void ClearDeviceTree();
    void DisconnectAllStream(bool bIsAsync);

    static void playerCallback(void *_this, int id, CVideoFrame frame);

private:
    Ui::LiveViewWidget m_ui;
    CPlayerCtrl m_pPlayerCtrl;
    QMap<int, int> m_pDeviceID2StreamID;
};
