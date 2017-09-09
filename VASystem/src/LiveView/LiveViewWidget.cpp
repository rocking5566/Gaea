#include "LiveViewWidget.h"
#include "Device/DeviceModel.h"

CLiveViewWidget::CLiveViewWidget(QWidget *parent)
    : CTabEntity(parent)
{
    m_ui.setupUi(this);
}

CLiveViewWidget::~CLiveViewWidget()
{

}

void CLiveViewWidget::Enter()
{
    InitDeviceTree();
}

void CLiveViewWidget::Leave()
{
    // [TODO]
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
