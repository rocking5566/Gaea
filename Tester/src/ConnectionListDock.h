#ifndef ConnectionListDock_h__
#define ConnectionListDock_h__

#include <QDockWidget>
#include <QStandardItemModel>
#include "StreamEngineTypes.h"
#include "ui_ConnectionListWidget.h"

class CPlayerCtrl;

class CConnectionListDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit CConnectionListDock(CPlayerCtrl* pPlayerCtrl, QWidget *parent = 0);
    ~CConnectionListDock();

private slots:
    void OnOpenRTSP();
    void OnOpenWebCam();
    void OnCloseStream();

private:
    void InitConnectionTable();
    void AddConnectionToTable(int id, const SConnectInfo& rInfo);
    void RemoveConnectionFromTable(int id);

private:
    Ui::ConnectionListWidget m_ui;
    CPlayerCtrl* m_pPlayerCtrl;
    QStandardItemModel m_tableModel;
};
#endif // ConnectionListDock_h__
