#include "RegisterFaceWidget.h"
#include "FaceDataBase.h"

CRegisterFaceWidget::CRegisterFaceWidget(QWidget *parent /*= 0*/)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    ConnectUISignal();
    InitTreeWidget();
}

CRegisterFaceWidget::~CRegisterFaceWidget()
{

}

void CRegisterFaceWidget::InitTreeWidget()
{
    // [TODO] Get data from database
}

void CRegisterFaceWidget::SetFaceConfigUIEnable(bool bEnable)
{
    m_ui.leName->setEnabled(bEnable);
    m_ui.leGender->setEnabled(bEnable);
    m_ui.leAge->setEnabled(bEnable);
    m_ui.btnWebCam->setEnabled(bEnable);
    m_ui.btnBrowse->setEnabled(bEnable);
}

void CRegisterFaceWidget::ConnectUISignal()
{
    connect(m_ui.btnAdd, SIGNAL(clicked()), this, SLOT(OnAddFace()));
    connect(m_ui.btnRemove, SIGNAL(clicked()), this, SLOT(OnRemoveFace()));
    connect(m_ui.treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnTreeWidgetSelectionChanged()));
    connect(m_ui.leName, SIGNAL(editingFinished()), this, SLOT(OnEditingNameFinished()));
    connect(m_ui.leGender, SIGNAL(editingFinished()), this, SLOT(OnEditingNameFinished()));
    connect(m_ui.leAge, SIGNAL(editingFinished()), this, SLOT(OnEditingNameFinished()));
    connect(m_ui.btnWebCam, SIGNAL(clicked()), this, SLOT(OnBtnWebCamClicked()));
    connect(m_ui.btnBrowse, SIGNAL(clicked()), this, SLOT(OnBtnBrowseClicked()));
}

void CRegisterFaceWidget::OnAddFace()
{
    int count = m_ui.treeWidget->topLevelItemCount();
    QString itemName = "Face" + QString::number(count);
    QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList(itemName));
    m_ui.treeWidget->addTopLevelItem(pItem);

    // [TODO] Update database
}

void CRegisterFaceWidget::OnRemoveFace()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        SAFE_DELETE(itemList[0]);
        // [TODO] Update database
    }
}

void CRegisterFaceWidget::OnTreeWidgetSelectionChanged()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    if (!itemList.empty())
    {
        SetFaceConfigUIEnable(true);
        // [TODO] Get selected item data from database
    }
    else
    {
        SetFaceConfigUIEnable(false);
    }
}

void CRegisterFaceWidget::OnEditingNameFinished()
{
    // [TODO] Update database
}

void CRegisterFaceWidget::OnEditingGenderFinished()
{
    // [TODO] Update database
}

void CRegisterFaceWidget::OnEditingAgeFinished()
{
    // [TODO] Update database
}

void CRegisterFaceWidget::OnBtnWebCamClicked()
{
    // [TODO] Design UI and update image database for web cam
}

void CRegisterFaceWidget::OnBtnBrowseClicked()
{
    // [TODO] Design UI and update image database for local file
}
