#include <QString>
#include <QDatetime>

struct EmotionKPI
{
    double m_Promoters;
    double m_Passives;
    double m_Detractors;
    double m_NetPromoterScore;

    EmotionKPI() : m_Promoters(0), m_Passives(0), m_Detractors(0), m_NetPromoterScore(0)
    {
    }
};

class CStatisticModel
{
public:
    static CStatisticModel* GetSingleTon();
    QStringList GetEmotionCategory();   //Supported
    void QueryAllEmotionsStatistic(const QDateTime& dtFrom, const QDateTime& dtTo, QList<int>& outEmotionStatistic, EmotionKPI& outKpi);   //All data
    QList<int> QueryEmotionsStatistic(const QDateTime& dtFrom, const QDateTime& dtTo, const QStringList& queryEmotions);
    QPair<int, int> QueryGenderStatistic(const QDateTime& dtFrom, const QDateTime& dtTo);   //First: Female, Second: Male
    QStringList GetAgesInterval();   //Age Bar chart category
    QList<int> QueryAgesStatistic(const QDateTime& dtFrom, const QDateTime& dtTo);

private:
    explicit CStatisticModel();
    ~CStatisticModel();
    static CStatisticModel* sm_Instance;
};
