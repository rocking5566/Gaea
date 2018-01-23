#include "SysConfigWidget.h"
#include "SysConfigModel.h"
#include <QMessageBox>

CSysConfigWidget::CSysConfigWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
{
    m_ui.setupUi(this);
    ConnectUISignal();
}

CSysConfigWidget::~CSysConfigWidget()
{
}

void CSysConfigWidget::Enter()
{
    qulonglong sysBankAreaCode = CSysConfigModel::GetSingleTon()->GetBankAreaCode();
    m_ui.leSysBankAreaCode->setText(QString::number(sysBankAreaCode));
}

void CSysConfigWidget::Leave()
{
    if (sender() == m_ui.leSysBankAreaCode)
    {
        CSysConfigModel::GetSingleTon()->SetBankAreaCode(m_ui.leSysBankAreaCode->text().toULongLong());
    }
}
void CSysConfigWidget::OnBtnClearAllSysDataClicked()
{
    int ret = QMessageBox::warning(this, tr("Face Recognition System"),
        tr("The will clear all system data.\n"
        "Including registered face database, device config, recognition result, system configuration"
        "Do you want to continue?"),
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::Yes);


    if (ret == QMessageBox::Yes)
    {
        // TODO
        // Remove data from CMemberModel, CDeviceModel, CSysConfigModel, Algorithm result
    }
}

void CSysConfigWidget::ConnectUISignal()
{
    connect(m_ui.btnClearAllSysData, SIGNAL(clicked()), this, SLOT(OnBtnClearAllSysDataClicked()));
}
