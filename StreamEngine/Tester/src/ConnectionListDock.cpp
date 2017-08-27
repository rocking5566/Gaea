#include "ConnectionListDock.h"
#include "PlayerCtrl.h"
#include <QInputDialog>

CConnectionListDock::CConnectionListDock(CPlayerCtrl* pPlayerCtrl, QWidget *parent /*= 0*/)
    : QDockWidget(parent)
    , m_pPlayerCtrl(pPlayerCtrl)
{
    QWidget* panel = new QWidget(this);
    m_ui.setupUi(panel);
    setWidget(panel);
    InitConnectionTable();

    connect(m_ui.btnOpenRtsp, SIGNAL(clicked()), this, SLOT(OnOpenRTSP()));
    connect(m_ui.btnOpenWebCam, SIGNAL(clicked()), this, SLOT(OnOpenWebCam()));
    connect(m_ui.btnCloseStream, SIGNAL(clicked()), this, SLOT(OnCloseStream()));
}

CConnectionListDock::~CConnectionListDock()
{
    int row = m_tableModel.rowCount();

    for (int i = 0; i < row; ++i)
    {
        QStandardItem* pItem = m_tableModel.item(row - 1, 0);
        m_pPlayerCtrl->DisConnect(pItem->text().toInt(), false);
    }
}

void CConnectionListDock::InitConnectionTable()
{
    QStringList horizontalHeader;
    horizontalHeader.append("ID");
    horizontalHeader.append("type");
    horizontalHeader.append("url");
    horizontalHeader.append("Status");
    m_tableModel.setHorizontalHeaderLabels(horizontalHeader);
    m_ui.tableView->setModel(&m_tableModel);
}

void CConnectionListDock::OnOpenRTSP()
{
    SConnectInfo info;

    bool bOk = false;
    info.m_type = eRTSP;
    info.m_sUrl = QInputDialog::getText(this, tr("Open RTSP"),
        tr("RTSP url:"), QLineEdit::Normal,
        "rtsp://127.0.0.1:8554/test.mkv", &bOk);

    if (bOk)
    {
        int id = m_pPlayerCtrl->Connect(info);
        AddConnectionToTable(id, info);
    }
    
}

void CConnectionListDock::OnOpenWebCam()
{
    SConnectInfo info;
    info.m_type = eWebCam;
    info.m_iWebCamDeviceID = 0;
    int id = m_pPlayerCtrl->Connect(info);
    AddConnectionToTable(id, info);
}

void CConnectionListDock::OnCloseStream()
{
    bool bOk = false;
    int id = QInputDialog::getInt(this, tr("Close Connection"),
        tr("Stream ID:"), 0, 0, 2147483647, 1, &bOk);

    if (bOk)
    {
        m_pPlayerCtrl->DisConnect(id, true);
        RemoveConnectionFromTable(id);
    }
}

void CConnectionListDock::AddConnectionToTable(int id, const SConnectInfo& rInfo)
{
    int row = m_tableModel.rowCount();

    m_tableModel.setItem(row, 0, new QStandardItem(QString::number(id)));

    switch (rInfo.m_type)
    {
    case eRTSP:
        m_tableModel.setItem(row, 1, new QStandardItem("RTSP"));
        m_tableModel.setItem(row, 2, new QStandardItem(rInfo.m_sUrl));
        break;

    case eWebCam:
        m_tableModel.setItem(row, 1, new QStandardItem("Web Cam"));
        break;
    }
    
    m_ui.tableView->resizeColumnsToContents();
}

void CConnectionListDock::RemoveConnectionFromTable(int id)
{
    int row = m_tableModel.rowCount();

    for (int i = 0; i < row; ++i)
    {
        QStandardItem* pItem = m_tableModel.item(row - 1, 0);
        
        if (pItem->text().toInt() == id)
        {
            m_tableModel.removeRow(i);
        }
    }
}
