#include "Tab/TabEntity.h"
#include "ui_LiveViewWidget.h"
#include "PlayerCtrl.h"
#include "ImageAdaptor.h"

class CFacialInfoWidget;

class CLiveViewWidget : public CTabEntity
{
    Q_OBJECT

public:
    explicit CLiveViewWidget(QWidget *parent = 0);
    ~CLiveViewWidget();

    // override CTabEntity
    virtual void Enter();
    virtual void Leave();

protected:
    virtual void hideEvent(QHideEvent *event);

private slots:
    void OnCurrentItemChanged(QTreeWidgetItem *pCurrent, QTreeWidgetItem *pPrevious);
    void OnSnapshot();

private:
    void ConnectUISignal();
    void SetupDeviceTree();
    void ClearDeviceTree();
    void DisconnectAllStream(bool bIsAsync);

    static void playerCallback(void *_this, int id, CImageAdaptor frame);

private:
    Ui::LiveViewWidget m_ui;
    CPlayerCtrl m_pPlayerCtrl;
    CFacialInfoWidget* m_pFacialWidget;
    QMap<int, int> m_mapDeviceID2StreamID;
};
