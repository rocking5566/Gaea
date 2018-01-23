#include "RegisterFaceWidget.h"
#include <QFileDialog>
#include "MemberModel.h"

CRegisterFaceWidget::CRegisterFaceWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
    , m_iWebCamStreamId(-1)
{
    m_ui.setupUi(this);
    ConnectUISignal();
    InitTreeWidget();
}

CRegisterFaceWidget::~CRegisterFaceWidget()
{
    m_pPlayerCtrl.DisConnect(m_iWebCamStreamId, false);
}

void CRegisterFaceWidget::Enter()
{
    // [TODO]
}

void CRegisterFaceWidget::Leave()
{
    m_pPlayerCtrl.DisConnect(m_iWebCamStreamId, false);
}

void CRegisterFaceWidget::InitTreeWidget()
{
    // [TODO] Get data from database
}

void CRegisterFaceWidget::SetFaceEntityUIEnable(bool bEnable)
{
    m_ui.leName->setEnabled(bEnable);
    m_ui.cbGender->setEnabled(bEnable);
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
    connect(m_ui.cbGender, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(OnCbGenderChanged(const QString&)));
    connect(m_ui.btnWebCam, SIGNAL(clicked()), this, SLOT(OnBtnWebCamClicked()));
    connect(m_ui.btnBrowse, SIGNAL(clicked()), this, SLOT(OnBtnBrowseClicked()));
}

void CRegisterFaceWidget::OnAddFace()
{
    int count = m_ui.treeWidget->topLevelItemCount();
    QString itemName = "Face_" + QString::number(count);
    QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList(itemName));

    SMemberProperty member(itemName, eMale, 0);
    int memberId = CMemberModel::GetSingleTon()->AddMember(member);
    pItem->setData(0, Qt::UserRole, memberId);
    m_ui.treeWidget->addTopLevelItem(pItem);
}

void CRegisterFaceWidget::OnRemoveFace()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        int memberId = itemList[0]->data(0, Qt::UserRole).toInt();
        CMemberModel::GetSingleTon()->RemoveMember(memberId);
        SAFE_DELETE(itemList[0]);
    }
}

void CRegisterFaceWidget::OnTreeWidgetSelectionChanged()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    SMemberProperty member;

    if (!itemList.empty())
    {
        SetFaceEntityUIEnable(true);
        int memberId = itemList[0]->data(0, Qt::UserRole).toInt();
        CMemberModel::GetSingleTon()->GetMember(memberId, member);
        m_ui.leName->setText(member.m_name);
        m_ui.cbGender->setCurrentIndex(member.m_gender);
    }
    else
    {
        SetFaceEntityUIEnable(false);
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

    if (!itemList.empty())
    {
        int id = itemList[0]->data(0, Qt::UserRole).toInt();

        if (sender() == m_ui.leName)
        {
            CMemberModel::GetSingleTon()->EditName(id, m_ui.leName->text());
        }
    }
}

void CRegisterFaceWidget::OnCbGenderChanged(const QString & text)
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        int memberId = itemList[0]->data(0, Qt::UserRole).toInt();
        CMemberModel::GetSingleTon()->EditGender(memberId, StringToGender(text));
    }
}

void CRegisterFaceWidget::OnBtnWebCamClicked()
{
    // [TODO] Disconnect and Enable the button when register completed
    m_ui.btnWebCam->setDisabled(true);

    SConnectInfo info;
    info.m_type = eWebCam;
    m_iWebCamStreamId = m_pPlayerCtrl.Connect(info);
    m_pPlayerCtrl.AttachStream(m_iWebCamStreamId, playerCallback, this);
}

void CRegisterFaceWidget::OnBtnBrowseClicked()
{
    // [TODO] Pass images to register
    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "Select one or more images to register",
        ".",
        "Images (*.png *.jpg)");
}

void CRegisterFaceWidget::playerCallback(void *_this, int streamId, CImageAdaptor frame)
{
    Q_UNUSED(streamId);
    CRegisterFaceWidget* This = (CRegisterFaceWidget*)_this;
    This->m_ui.renderWidget->Render(frame);
}
