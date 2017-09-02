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
    connect(m_ui.leName, SIGNAL(textChanged(const QString &)), this, SLOT(OnNameChanged(const QString &)));
    connect(m_ui.leName, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));
    connect(m_ui.leGender, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));
    connect(m_ui.leAge, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));
    connect(m_ui.btnWebCam, SIGNAL(clicked()), this, SLOT(OnBtnWebCamClicked()));
    connect(m_ui.btnBrowse, SIGNAL(clicked()), this, SLOT(OnBtnBrowseClicked()));
}

void CRegisterFaceWidget::OnAddFace()
{
    int count = m_ui.treeWidget->topLevelItemCount();
    QString itemName = "Face_" + QString::number(count);
    QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList(itemName));

    SFaceEntity ent(itemName, eMale, 0);
    int id = CFaceDataBase::GetSingleTon()->AddFace(ent);
    pItem->setData(0, Qt::UserRole, id);
    m_ui.treeWidget->addTopLevelItem(pItem);
}

void CRegisterFaceWidget::OnRemoveFace()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        int id = itemList[0]->data(0, Qt::UserRole).toInt();
        CFaceDataBase::GetSingleTon()->RemoveFace(id);
        SAFE_DELETE(itemList[0]);
    }
}

void CRegisterFaceWidget::OnTreeWidgetSelectionChanged()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    SFaceEntity ent;

    if (!itemList.empty())
    {
        SetFaceConfigUIEnable(true);
        int id = itemList[0]->data(0, Qt::UserRole).toInt();
        CFaceDataBase::GetSingleTon()->GetFace(id, ent);
        m_ui.leName->setText(ent.m_name);
        m_ui.leGender->setText(GenderToString(ent.m_gender));
        m_ui.leAge->setText(QString::number(ent.m_age));
    }
    else
    {
        SetFaceConfigUIEnable(false);
    }
}

void CRegisterFaceWidget::OnNameChanged(const QString& rText)
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        itemList[0]->setText(0, rText);
    }
}

void CRegisterFaceWidget::OnEditingFinished()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    SFaceEntity ent;

    if (!itemList.empty())
    {
        int id = itemList[0]->data(0, Qt::UserRole).toInt();

        if (sender() == m_ui.leName)
        {
            CFaceDataBase::GetSingleTon()->EditName(id, m_ui.leName->text());
        }
        else if (sender() == m_ui.leGender)
        {
            CFaceDataBase::GetSingleTon()->EditGender(id, StringToGender(m_ui.leGender->text()));
        }
        else if (sender() == m_ui.leAge)
        {
            CFaceDataBase::GetSingleTon()->EditAge(id, m_ui.leAge->text().toInt());
        }

    }
}

void CRegisterFaceWidget::OnBtnWebCamClicked()
{
    // [TODO] Design UI and update image database for web cam
}

void CRegisterFaceWidget::OnBtnBrowseClicked()
{
    // [TODO] Design UI and update image database for local file
}
