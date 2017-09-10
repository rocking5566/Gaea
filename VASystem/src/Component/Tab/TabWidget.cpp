#include "TabWidget.h"
#include "TabEntity.h"

CTabWidget::CTabWidget(QWidget *parent)
    : QTabWidget(parent)
    , m_pPreviousTab(NULL)
{
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(OnCurrentChanged(int)));
}

CTabWidget::~CTabWidget()
{

}

void CTabWidget::OnCurrentChanged(int index)
{
    CTabEntity* pCurrentTab = dynamic_cast<CTabEntity*>(widget(index));

    if (m_pPreviousTab)
    {
        m_pPreviousTab->Leave();
    }

    if (pCurrentTab)
    {
        pCurrentTab->Enter();
    }

    m_pPreviousTab = pCurrentTab;
}
