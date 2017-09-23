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
    QList<int> QueryEmotionsCount(const QDateTime& dtFrom, const QDateTime& dtTo, const QList<Emotion>& queryEmotions);

private:
    explicit CStatisticModel();
    ~CStatisticModel();
    static CStatisticModel* sm_Instance;
};
