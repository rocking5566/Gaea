#include "StatisticWidget.h"
#include "BarChart.h"

CStatisticWidget::CStatisticWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
    , m_pBarChart(NULL)
{
    m_ui.setupUi(this);

    m_pBarChart = new CBarChart(eVertical, { "angry", "disgust", "fear", "happy", "sad", "surprise", "neutral" }, this);
    m_ui.contentLayout->addWidget(m_pBarChart, 1, 0);

    m_ui.dtEditFrom->setDate(QDate::currentDate());
    m_ui.dtEditTo->setDateTime(QDateTime::currentDateTime());
}

CStatisticWidget::~CStatisticWidget()
{

}

void CStatisticWidget::Enter()
{

}

void CStatisticWidget::Leave()
{

}

