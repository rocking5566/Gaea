#include "StatisticModel.h"
#include <ctime>
#include <QApplication>

CStatisticModel* CStatisticModel::sm_Instance = NULL;

CStatisticModel* CStatisticModel::GetSingleTon()
{
    if (sm_Instance == NULL)
    {
        sm_Instance = new CStatisticModel();
    }

    return sm_Instance;
}

CStatisticModel::CStatisticModel()
{

}

CStatisticModel::~CStatisticModel()
{

}

void CStatisticModel::QueryAllEmotionsStatistic(const QDateTime& dtFrom, const QDateTime& dtTo, QList<int>& outEmotionStatistic, EmotionKPI& outKpi)
{
    const QList<Emotion> query = {eAngry, eDisgust, eFear, eHappy, eSad, eSurprise, eNeutral};
    outEmotionStatistic = QueryEmotionsStatistic(dtFrom, dtTo, query);

    // [TODO] Calculate KPI
    qsrand((unsigned)time(NULL) + qApp->applicationPid());
    outKpi.m_Detractors = qrand() % 100 + 1;
    outKpi.m_Passives = qrand() % 100 + 1;
    outKpi.m_Promoters = qrand() % 100 + 1;
    outKpi.m_NetPromoterScore = qrand() % 100 + 1;
}

QList<int> CStatisticModel::QueryEmotionsStatistic(const QDateTime& dtFrom, const QDateTime& dtTo, const QList<Emotion>& queryEmotions)
{
    // [TODO] Get data from Database
    // Following code just generate random number list
    Q_UNUSED(dtFrom);
    Q_UNUSED(dtTo);

    QList<int> ret;
    qsrand((unsigned)time(NULL) + qApp->applicationPid());

    for (int i = 0; i < queryEmotions.size(); ++i)
    {
        ret << qrand() % 10 + 1;
    }

    return std::move(ret);
}

QPair<int, int> CStatisticModel::QueryGenderStatistic(const QDateTime& dtFrom, const QDateTime& dtTo)
{
    // [TODO] Get data from Database
    // Following code just generate random number
    Q_UNUSED(dtFrom);
    Q_UNUSED(dtTo);

    QPair<int, int> ret;
    qsrand((unsigned)time(NULL) + qApp->applicationPid());
    ret.first = qrand() % 100 + 1;
    ret.second = qrand() % 100 + 1;

    return std::move(ret);
}

