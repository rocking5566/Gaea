#include "HomeWindow.h"
#include "PlayerWidget.h"
#include "PlayerCtrl.h"
#include "Util.h"
#include "ConnectionListDock.h"

CHomeWindow::CHomeWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_pPlayerCtrl(new CPlayerCtrl(this))
    , m_pConnectionListDock(NULL)
{
    m_ui.setupUi(this);

    m_pConnectionListDock = new CConnectionListDock(m_pPlayerCtrl, this);
    addDockWidget(Qt::LeftDockWidgetArea, m_pConnectionListDock);
    m_pConnectionListDock->setFloating(true);

    connect(m_ui.btnAddPlayer, SIGNAL(clicked()), this, SLOT(OnAddPlayer()));
    connect(m_ui.btnRemovePlayer, SIGNAL(clicked()), this, SLOT(OnRemovePlayer()));
}

CHomeWindow::~CHomeWindow()
{
    foreach (CPlayerWidget* pWidget, m_PlayerWidgetList)
    {
        SAFE_DELETE(pWidget);
    }

    SAFE_DELETE(m_pConnectionListDock);
    SAFE_DELETE(m_pPlayerCtrl);
}

void CHomeWindow::OnAddPlayer()
{
    CPlayerWidget* pWidget = new CPlayerWidget(m_pPlayerCtrl);
    m_PlayerWidgetList << pWidget;
    int columnCount = m_ui.gridLayout->columnCount();
    m_ui.gridLayout->addWidget(pWidget, 0, columnCount);
}

void CHomeWindow::OnRemovePlayer()
{
    int widgetCount = m_ui.gridLayout->count();

    if (widgetCount > 0)
    {
        QWidget* pWidget = m_ui.gridLayout->takeAt(widgetCount - 1)->widget();
        m_PlayerWidgetList.pop_back();
        SAFE_DELETE(pWidget);
    }
}
