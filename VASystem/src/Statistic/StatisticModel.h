#include <QString>
#include <QDatetime>

enum Emotion
{
    eAngry,
    eDisgust,
    eFear,
    eHappy,
    eSad,
    eSurprise,
    eNeutral,
};

class CStatisticModel
{
public:
    static CStatisticModel* GetSingleTon();
    QList<int> QueryEmotionsStatistic(const QDateTime& dtFrom, const QDateTime& dtTo, const QList<Emotion>& queryEmotions);
    QPair<int, int> QueryGenderStatistic(const QDateTime& dtFrom, const QDateTime& dtTo);   //First: Female, Second: Male

private:
    explicit CStatisticModel();
    ~CStatisticModel();
    static CStatisticModel* sm_Instance;
};
