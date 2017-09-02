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

}

void CConfigDeviceWidget::InitTreeWidget()
{
    // [TODO] Get data from CDeviceModel
}

void CConfigDeviceWidget::SetDeviceEntityUIEnable(bool bEnable)
{
    m_ui.leName->setEnabled(bEnable);
    m_ui.leUrl->setEnabled(bEnable);
    m_ui.lePort->setEnabled(bEnable);
    m_ui.leUser->setEnabled(bEnable);
    m_ui.lePassword->setEnabled(bEnable);
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
    connect(m_ui.lePort, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));
    connect(m_ui.leUser, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));
    connect(m_ui.lePassword, SIGNAL(editingFinished()), this, SLOT(OnEditingFinished()));

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
    // [TODO] Testing the RTSP 
}
