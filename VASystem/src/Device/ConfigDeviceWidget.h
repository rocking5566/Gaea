#ifndef ConfigDeviceWidget_h__
#define ConfigDeviceWidget_h__

#include "Tab/TabEntity.h"
#include "ui_ConfigDeviceWidget.h"
#include "PlayerCtrl.h"
#include "ImageAdaptor.h"

class CConfigDeviceWidget : public CTabEntity
{
    Q_OBJECT

public:
    explicit CConfigDeviceWidget(QWidget *parent = 0);
    ~CConfigDeviceWidget();

    // override CTabEntity
    virtual void Enter();
    virtual void Leave();

private slots:
    void OnAddDevice();
    void OnRemoveDevice();
    void OnTreeWidgetSelectionChanged();
    void OnNameChanged(const QString& rText);
    void OnEditingFinished();
    void OnBtnPlayClicked();

private:
    void ConnectUISignal();
    void InitDeviceTree();
    void SetDeviceEntityUIEnable(bool bEnable);

    static void playerCallback(void *_this, int id, CImageAdaptor frame);

private:
    Ui::ConfigDeviceWidget m_ui;
    CPlayerCtrl m_pPlayerCtrl;
    int m_curStreamId;
};
#endif // ConfigDeviceWidget_h__
