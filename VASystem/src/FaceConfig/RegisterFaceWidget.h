#ifndef RegisterFaceWidget_h__
#define RegisterFaceWidget_h__

#include "Tab/TabEntity.h"
#include "PlayerCtrl.h"
#include "ImageAdaptor.h"
#include "ui_RegisterFaceWidget.h"

class CRegisterFaceWidget : public CTabEntity
{
    Q_OBJECT

public:
    explicit CRegisterFaceWidget(QWidget *parent = 0);
    ~CRegisterFaceWidget();

    // override CTabEntity
    virtual void Enter();
    virtual void Leave();

private slots:
    void OnAddFace();
    void OnRemoveFace();
    void OnTreeWidgetSelectionChanged();
    void OnNameChanged(const QString& rText);
    void OnEditingFinished();
    void OnCbGenderChanged(const QString & text);
    void OnBtnWebCamClicked();
    void OnBtnBrowseClicked();

private:
    void ConnectUISignal();
    void InitTreeWidget();
    void SetFaceEntityUIEnable(bool bEnable);

    static void playerCallback(void *_this, int id, CImageAdaptor frame);

private:
    Ui::RegisterFaceWidget m_ui;
    CPlayerCtrl m_playerCtrl;
    int m_iWebCamStreamId;

};
#endif // RegisterFaceWidget_h__
