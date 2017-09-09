#include "LiveViewWidget.h"
#include "Device/DeviceModel.h"

CLiveViewWidget::CLiveViewWidget(QWidget *parent)
    : CTabEntity(parent)
    , m_curStreamId(-1)
{
    m_ui.setupUi(this);
    ConnectUISignal();
}

CLiveViewWidget::~CLiveViewWidget()
{
    m_pPlayerCtrl.DisConnect(m_curStreamId, false);
}

void CLiveViewWidget::Enter()
{
    InitDeviceTree();
}

void CLiveViewWidget::Leave()
{
    m_pPlayerCtrl.DisConnect(m_curStreamId, false);
}

void CLiveViewWidget::InitDeviceTree()
{
    m_ui.treeWidget->clear();

    QMap<int, SDeviceProperty> deviceMap;
    CDeviceModel::GetSingleTon()->GetDevices(deviceMap);

    auto iter = deviceMap.constBegin();
    while (iter != deviceMap.constEnd())
    {
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList(iter.value().m_name));
        pItem->setData(0, Qt::UserRole, iter.key());
        m_ui.treeWidget->addTopLevelItem(pItem);
        ++iter;
    }
}

void CLiveViewWidget::ConnectUISignal()
{
    connect(m_ui.treeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnTreeWidgetSelectionChanged()));
}

void CLiveViewWidget::OnTreeWidgetSelectionChanged()
{
    SConnectInfo info;
    SDeviceProperty dev;
    QList<QTreeWidgetItem *> itemList = m_ui.treeWidget->selectedItems();
    m_pPlayerCtrl.DisConnect(m_curStreamId, true);

    if (!itemList.empty())
    {
        int id = itemList[0]->data(0, Qt::UserRole).toInt();
        CDeviceModel::GetSingleTon()->GetDevice(id, dev);

        info.m_type = eRTSP;
        info.m_sUrl = dev.m_url;

        // [TODO] Connect all the streams when initializing device tree
        m_curStreamId = m_pPlayerCtrl.Connect(info);
        m_pPlayerCtrl.AttachStream(m_curStreamId, playerCallback, this);
    }
}

void CLiveViewWidget::playerCallback(void *_this, int id, CVideoFrame frame)
{
    Q_UNUSED(id);
    CLiveViewWidget* This = (CLiveViewWidget*)_this;
    This->m_ui.renderWidget->Render(frame);
}
