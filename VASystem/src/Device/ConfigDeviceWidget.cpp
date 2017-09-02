#include "ConfigDeviceWidget.h"

CConfigDeviceWidget::CConfigDeviceWidget(QWidget *parent /*= 0*/)
    : QWidget(parent)
    , m_curStreamId(-1)
{
    m_ui.setupUi(this);
    ConnectUISignal();
    InitTreeWidget();
}

CConfigDeviceWidget::~CConfigDeviceWidget()
{
    m_pPlayerCtrl.DisConnect(m_curStreamId, false);
}

void CConfigDeviceWidget::InitTreeWidget()
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

    // [TODO] update DeviceModel
    m_ui.treeWidget->addTopLevelItem(pItem);
}

void CConfigDeviceWidget::OnRemoveDevice()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();

    if (!itemList.empty())
    {
        // [TODO] update DeviceModel
        SAFE_DELETE(itemList[0]);
    }
}

void CConfigDeviceWidget::OnTreeWidgetSelectionChanged()
{
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    m_pPlayerCtrl.DisConnect(m_curStreamId, true);

    if (!itemList.empty())
    {
        SetDeviceEntityUIEnable(true);
        // [TODO] Get data from DeviceModel
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

    if (!itemList.empty())
    {
        // [TODO] update DeviceModel
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

void CConfigDeviceWidget::playerCallback(void *_this, int id, CVideoFrame frame)
{
    Q_UNUSED(id);
    CConfigDeviceWidget* This = (CConfigDeviceWidget*)_this;
    This->m_ui.renderWidget->Render(frame);
}
