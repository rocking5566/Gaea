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

QList<int> CStatisticModel::QueryEmotionsCount(const QDateTime& dtFrom, const QDateTime& dtTo, const QList<Emotion>& queryEmotions)
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

