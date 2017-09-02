#ifndef RegisterFaceWidget_h__
#define RegisterFaceWidget_h__

#include <QMainWindow>
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
    void OnBtnWebCamClicked();
    void OnBtnBrowseClicked();

private:
    void ConnectUISignal();
    void InitTreeWidget();
    void SetFaceConfigUIEnable(bool bEnable);

private:
    Ui::RegisterFaceWidget m_ui;

};
#endif // RegisterFaceWidget_h__
