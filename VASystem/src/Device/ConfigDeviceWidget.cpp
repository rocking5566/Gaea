#include "ConfigDeviceWidget.h"
#include "DeviceModel.h"

CConfigDeviceWidget::CConfigDeviceWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
    , m_curStreamId(-1)
{
    m_ui.setupUi(this);
    ConnectUISignal();
    InitDeviceTree();
}

CConfigDeviceWidget::~CConfigDeviceWidget()
{
    m_pPlayerCtrl.DisConnect(m_curStreamId, false);
}

void CConfigDeviceWidget::Enter()
{
    // [TODO]
}

void CConfigDeviceWidget::Leave()
{
    m_pPlayerCtrl.DisConnect(m_curStreamId, false);
}

void CConfigDeviceWidget::InitDeviceTree()
{
    // [TODO] Get data from CDeviceModel
}

void CConfigDeviceWidget::SetDeviceEntityUIEnable(bool bEnable)
{
    m_ui.leName->setEnabled(bEnable);
    m_ui.leUrl->setEnabled(bEnable);
    m_ui.renderWidget->setEnabled(bEnable);
    m_ui.btnPlay->setEnabled(bEnable);
}

void CConfigDeviceWidget::ConnectUISignal()
{
    connect(m_ui.btnAdd, SIGNAL(clicked()), this, SLOT(OnAddDevice()));
    connect(m_ui.btnRemove, SIGNAL(clicked()), this, SLOT(OnRemoveDevice()));
    connect(m_ui.treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnTreeWidgetSelectionChanged()));
    connect(m_ui.leName, SIGNAL(textChanged(const QString &)), this, SLOT(OnNameChanged(const QString &)));

    connect(m_ui.leName, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));
    connect(m_ui.leUrl, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));

    connect(m_ui.btnPlay, SIGNAL(clicked()), this, SLOT(OnBtnPlayClicked()));
}

void CConfigDeviceWidget::OnAddDevice()
{
    int count = m_ui.treeWidget->topLevelItemCount();
    QString itemName = "Device_" + QString::number(count);
    QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList(itemName));

    SDeviceProperty dev(itemName, "");
    int id = CDeviceModel::GetSingleTon()->AddDevice(dev);
    pItem->setData(0, Qt::UserRole, id);
    m_ui.treeWidget->addTopLevelItem(pItem);
}

void CConfigDeviceWidget::OnRemoveDevice()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        int id = itemList[0]->data(0, Qt::UserRole).toInt();
        CDeviceModel::GetSingleTon()->RemoveDevice(id);
        SAFE_DELETE(itemList[0]);
    }
}

void CConfigDeviceWidget::OnTreeWidgetSelectionChanged()
{
    SDeviceProperty dev;
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    m_pPlayerCtrl.DisConnect(m_curStreamId, true);

    if (!itemList.empty())
    {
        SetDeviceEntityUIEnable(true);
        int id = itemList[0]->data(0, Qt::UserRole).toInt();
        CDeviceModel::GetSingleTon()->GetDevice(id, dev);
        m_ui.leName->setText(dev.m_name);
        m_ui.leUrl->setText(dev.m_url);
    }
    else
    {
        SetDeviceEntityUIEnable(false);
    }
}

void CConfigDeviceWidget::OnNameChanged(const QString& rText)
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        itemList[0]->setText(0, rText);
    }
}

void CConfigDeviceWidget::OnEditingFinished()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    SDeviceProperty dev;

    if (!itemList.empty())
    {
        int id = itemList[0]->data(0, Qt::UserRole).toInt();
        dev.m_name = m_ui.leName->text();
        dev.m_url = m_ui.leUrl->text();

        CDeviceModel::GetSingleTon()->EditDevice(id, dev);
    }
}

void CConfigDeviceWidget::OnBtnPlayClicked()
{
    // Disconnect previous stream first
    m_pPlayerCtrl.DisConnect(m_curStreamId, true);

    SConnectInfo info;
    info.m_type = eRTSP;
    info.m_sUrl = m_ui.leUrl->text();
    m_curStreamId = m_pPlayerCtrl.Connect(info);
    m_pPlayerCtrl.AttachStream(m_curStreamId, playerCallback, this);
}

void CConfigDeviceWidget::playerCallback(void *_this, int id, CImageAdaptor frame)
{
    Q_UNUSED(id);
    CConfigDeviceWidget* This = (CConfigDeviceWidget*)_this;
    This->m_ui.renderWidget->Render(frame);
}
