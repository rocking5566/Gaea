#include "StatisticWidget.h"
#include "StatisticModel.h"
#include "BarChart.h"

CStatisticWidget::CStatisticWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
    , m_pEmotionKPIBarChart(NULL)
    , m_pEmotionStatisticBarChart(NULL)
    , m_pGenderStatisticBarChart(NULL)
    , m_pAgeStatisticBarChart(NULL)
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

    QStringList emotionCategory = CStatisticModel::GetSingleTon()->GetEmotionCategory();
    m_pEmotionStatisticBarChart = new CBarChart(eVertical, emotionCategory, this);
    m_pEmotionStatisticBarChart->SetValueAxisInteger(true);
    m_pEmotionStatisticBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_pEmotionStatisticBarChart->SetTitle("Total customers: Sentimental & Emotional analysis");

    m_pGenderStatisticBarChart = new CBarChart(eVertical, { "Female", "Male" }, this);
    m_pGenderStatisticBarChart->SetValueAxisInteger(true);
    m_pGenderStatisticBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_pGenderStatisticBarChart->SetTitle("Total customers: Female & Male analysis");

    QStringList agesInterval = CStatisticModel::GetSingleTon()->GetAgesInterval();
    m_pAgeStatisticBarChart = new CBarChart(eVertical, agesInterval, this);
    m_pAgeStatisticBarChart->SetValueAxisInteger(true);
    m_pAgeStatisticBarChart->SetTitleFont(QFont("Times", 16, QFont::Bold));
    m_pAgeStatisticBarChart->SetTitle("Total customers: Age analysis");

    m_ui.contentLayout->addWidget(m_pEmotionKPIBarChart, 0, 0);
    m_ui.contentLayout->addWidget(m_pEmotionStatisticBarChart, 0, 1);
    m_ui.contentLayout->addWidget(m_pGenderStatisticBarChart, 1, 0);
    m_ui.contentLayout->addWidget(m_pAgeStatisticBarChart, 1, 1);

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
    QList<int> agesStatistic;
    EmotionKPI kpi;

    CStatisticModel::GetSingleTon()->QueryAllEmotionsStatistic(dtFrom, dtTo, emotionStatistic, kpi);
    const QPair<int, int> genderStatistic = CStatisticModel::GetSingleTon()->QueryGenderStatistic(dtFrom, dtTo);
    agesStatistic = CStatisticModel::GetSingleTon()->QueryAgesStatistic(dtFrom, dtTo);

    m_pEmotionKPIBarChart->Clear();
    m_pEmotionKPIBarChart->PushData(QList<double>({kpi.m_Promoters, kpi.m_Passives, kpi.m_Detractors}));
    m_pEmotionKPIBarChart->SetTitle("NPS Score = " + QString::number(kpi.m_NetPromoterScore));

    m_pEmotionStatisticBarChart->Clear();
    m_pEmotionStatisticBarChart->PushData(emotionStatistic);

    m_pGenderStatisticBarChart->Clear();
    m_pGenderStatisticBarChart->PushData(QList<int>({genderStatistic.first, genderStatistic.second}));

    m_pAgeStatisticBarChart->Clear();
    m_pAgeStatisticBarChart->PushData(agesStatistic);
}

