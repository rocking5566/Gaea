#include "LiveViewWidget.h"
#include "Device/DeviceModel.h"
#include "FacialInfoWidget.h"

CLiveViewWidget::CLiveViewWidget(QWidget *parent)
    : CTabEntity(parent)
    , m_pFacialWidget(NULL)
{
    m_ui.setupUi(this);
    ConnectUISignal();
    m_pFacialWidget = new CFacialInfoWidget(parent);
}

CLiveViewWidget::~CLiveViewWidget()
{
    DisconnectAllStream(false);
    SAFE_DELETE(m_pFacialWidget);
}

void CLiveViewWidget::Enter()
{
    m_pFacialWidget->show();
    ClearDeviceTree();
    SetupDeviceTree();
}

void CLiveViewWidget::Leave()
{
    m_pFacialWidget->hide();
    DisconnectAllStream(true);
    ClearDeviceTree();
}

void CLiveViewWidget::SetupDeviceTree()
{
    QMap<int, SDeviceProperty> deviceMap;
    CDeviceModel::GetSingleTon()->GetDevices(deviceMap);

    auto iter = deviceMap.constBegin();
    while (iter != deviceMap.constEnd())
    {
        SConnectInfo info;
        QTreeWidgetItem* pItem = new QTreeWidgetItem(QStringList(iter.value().m_name));
        pItem->setData(0, Qt::UserRole, iter.key());
        m_ui.treeWidget->addTopLevelItem(pItem);

        info.m_type = eRTSP;
        info.m_sUrl = iter.value().m_url;

        // [TODO] Add API to Connect list of SConnectInfo in CPlayerCtrl simultaneously
        // Prevent block in worker thread, UI will also be blocked
        m_mapDeviceID2StreamID[iter.key()] = m_playerCtrl.Connect(info);
        ++iter;
    }
}

void CLiveViewWidget::ClearDeviceTree()
{
    m_ui.treeWidget->clear();
}

void CLiveViewWidget::ConnectUISignal()
{
    connect(m_ui.treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(OnCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));
    connect(m_ui.btnSnapshot, SIGNAL(clicked()), this, SLOT(OnSnapshot()));
}

void CLiveViewWidget::DisconnectAllStream(bool bIsAsync)
{
    auto iter = m_mapDeviceID2StreamID.constBegin();
    while (iter != m_mapDeviceID2StreamID.constEnd())
    {
        m_playerCtrl.DisConnect(iter.value(), bIsAsync);
        ++iter;
    }

    m_mapDeviceID2StreamID.clear();
}

void CLiveViewWidget::OnCurrentItemChanged(QTreeWidgetItem *pCurrent, QTreeWidgetItem *pPrevious)
{
    if (pPrevious)
    {
        int deviceID = pPrevious->data(0, Qt::UserRole).toInt();
        m_playerCtrl.DetachStream(m_mapDeviceID2StreamID[deviceID], this);
    }

    if (pCurrent)
    {
        int deviceID = pCurrent->data(0, Qt::UserRole).toInt();
        m_playerCtrl.AttachStream(m_mapDeviceID2StreamID[deviceID], playerCallback, this);
    }
}

void CLiveViewWidget::OnSnapshot()
{
    m_pFacialWidget->PushImage(m_ui.renderWidget->currentFrame());
}

void CLiveViewWidget::playerCallback(void *_this, int id, CImageAdaptor frame)
{
    Q_UNUSED(id);
    CLiveViewWidget* This = (CLiveViewWidget*)_this;
    This->m_ui.renderWidget->Render(frame);
}

void CLiveViewWidget::hideEvent(QHideEvent *event)
{
    m_pFacialWidget->hide();
    CTabEntity::hideEvent(event);
}
