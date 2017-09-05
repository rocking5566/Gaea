#ifndef RegisterFaceWidget_h__
#define RegisterFaceWidget_h__

#include <QMainWindow>
#include "PlayerCtrl.h"
#include "VideoFrame.h"
#include "ui_RegisterFaceWidget.h"

class CRegisterFaceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CRegisterFaceWidget(QWidget *parent = 0);
    ~CRegisterFaceWidget();

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

    static void playerCallback(void *_this, int id, CVideoFrame frame);

private:
    Ui::RegisterFaceWidget m_ui;
    CPlayerCtrl m_pPlayerCtrl;
    int m_iWebCamStreamId;

};
#endif // RegisterFaceWidget_h__
