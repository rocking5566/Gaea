#ifndef ConfigDeviceWidget_h__
#define ConfigDeviceWidget_h__

#include <QMainWindow>
#include "ui_ConfigDeviceWidget.h"
#include "PlayerCtrl.h"

class CConfigDeviceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CConfigDeviceWidget(QWidget *parent = 0);
    ~CConfigDeviceWidget();

private slots:
    void OnAddDevice();
    void OnRemoveDevice();
    void OnTreeWidgetSelectionChanged();
    void OnNameChanged(const QString& rText);
    void OnEditingFinished();
    void OnBtnPlayClicked();

private:
    void ConnectUISignal();
    void InitTreeWidget();
    void SetDeviceEntityUIEnable(bool bEnable);

private:
    Ui::ConfigDeviceWidget m_ui;
    CPlayerCtrl m_pPlayerCtrl;
    int m_curStreamId;
};
#endif // ConfigDeviceWidget_h__
