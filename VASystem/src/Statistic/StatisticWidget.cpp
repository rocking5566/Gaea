#include "StatisticWidget.h"
#include "StatisticModel.h"
#include "BarChart.h"

CStatisticWidget::CStatisticWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
    , m_pEmotionKPIBarChart(NULL)
    , m_pEmotionStatisticBarChart(NULL)
    , m_pGenderStatisticBarChart(NULL)
{
    m_ui.setupUi(this);

    InitUI();
}

CStatisticWidget::~CStatisticWidget()
{

}

void CStatisticWidget::InitUI()
{
    m_pEmotionKPIBarChart = new CBarChart(eVertical, {"Promoters", "Passives", "Detractors"}, this);
    m_pEmotionKPIBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_ui.contentLayout->addWidget(m_pEmotionKPIBarChart, 0, 0);

    m_pEmotionStatisticBarChart = new CBarChart(eVertical, { "angry", "disgust", "fear", "happy", "sad", "surprise", "neutral" }, this);
    m_pEmotionStatisticBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_pEmotionStatisticBarChart->SetTitle("Total customers: Sentimental & Emotional analysis");
    m_ui.contentLayout->addWidget(m_pEmotionStatisticBarChart, 0, 1);

    m_pGenderStatisticBarChart = new CBarChart(eVertical, { "Female", "Male" }, this);
    m_pGenderStatisticBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_pGenderStatisticBarChart->SetTitle("Total customers: Female & Male analysis");
    m_ui.contentLayout->addWidget(m_pGenderStatisticBarChart, 0, 2);

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
    QList<int> emotionStatistic;
    EmotionKPI kpi;

    CStatisticModel::GetSingleTon()->QueryAllEmotionsStatistic(dtFrom, dtTo, emotionStatistic, kpi);
    const QPair<int, int> genderStatistic = CStatisticModel::GetSingleTon()->QueryGenderStatistic(dtFrom, dtTo);

    m_pEmotionKPIBarChart->Clear();
    m_pEmotionKPIBarChart->PushData(QList<double>({kpi.m_Promoters, kpi.m_Passives, kpi.m_Detractors}));
    m_pEmotionKPIBarChart->SetTitle("NPS Score = " + QString::number(kpi.m_NetPromoterScore));

    m_pEmotionStatisticBarChart->Clear();
    m_pEmotionStatisticBarChart->PushData(emotionStatistic);

    m_pGenderStatisticBarChart->Clear();
    m_pGenderStatisticBarChart->PushData(QList<int>({genderStatistic.first, genderStatistic.second}));
}

