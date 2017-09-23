#include "StatisticWidget.h"
#include "StatisticModel.h"
#include "BarChart.h"

CStatisticWidget::CStatisticWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
    , m_pBarChart(NULL)
{
    m_ui.setupUi(this);

    InitUI();
}

CStatisticWidget::~CStatisticWidget()
{

}

void CStatisticWidget::InitUI()
{
    m_pBarChart = new CBarChart(eVertical, {"angry", "disgust", "fear", "happy", "sad", "surprise", "neutral"}, this);
    m_pBarChart->SetTitle("Emotion Statistic");
    m_ui.contentLayout->addWidget(m_pBarChart, 0, 0);

    m_ui.dtEditFrom->setDate(QDate::currentDate());
    m_ui.dtEditTo->setDateTime(QDateTime::currentDateTime());
}

void CStatisticWidget::Enter()
{
    // [TODO] - Update data when data is changed
    UpdateData();
}

void CStatisticWidget::Leave()
{

}

void CStatisticWidget::UpdateData()
{
    const QDateTime& dtFrom = QDateTime::currentDateTime();
    const QDateTime& dtTo = QDateTime::currentDateTime();
    const QList<Emotion> query = {eAngry, eDisgust, eFear, eHappy, eSad, eSurprise, eNeutral};

    const QList<int> data = CStatisticModel::GetSingleTon()->QueryEmotionsCount(dtFrom, dtTo, query);
    m_pBarChart->Clear();
    m_pBarChart->PushData(data);
}

