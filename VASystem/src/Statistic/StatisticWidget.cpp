#include "StatisticWidget.h"
#include "StatisticModel.h"
#include "BarChart.h"

CStatisticWidget::CStatisticWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
    , m_pEmotionBarChart(NULL)
    , m_pGenderBarChart(NULL)
{
    m_ui.setupUi(this);

    InitUI();
}

CStatisticWidget::~CStatisticWidget()
{

}

void CStatisticWidget::InitUI()
{
    m_pEmotionBarChart = new CBarChart(eVertical, {"angry", "disgust", "fear", "happy", "sad", "surprise", "neutral"}, this);
    m_pEmotionBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_pEmotionBarChart->SetTitle("Total customers: Sentimental & Emotional analysis");
    m_ui.contentLayout->addWidget(m_pEmotionBarChart, 0, 0);

    m_pGenderBarChart = new CBarChart(eVertical, { "Female", "Male" }, this);
    m_pGenderBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_pGenderBarChart->SetTitle("Total customers: Female & Male analysis");
    m_ui.contentLayout->addWidget(m_pGenderBarChart, 0, 1);

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

    const QList<int> emotionStatistic = CStatisticModel::GetSingleTon()->QueryEmotionsStatistic(dtFrom, dtTo, query);
    const QPair<int, int> genderStatistic = CStatisticModel::GetSingleTon()->QueryGenderStatistic(dtFrom, dtTo);

    m_pEmotionBarChart->Clear();
    m_pEmotionBarChart->PushData(emotionStatistic);

    m_pGenderBarChart->Clear();
    m_pGenderBarChart->PushData(QList<int>({genderStatistic.first, genderStatistic.second}));
}

