#ifndef BarChart_h__
#define BarChart_h__

#include <QGridLayout>
#include <QWidget>

#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QHorizontalBarSeries>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

enum BarType
{
    eVertical,
    eHorizontal,
};

class CBarChart : public QWidget
{
    Q_OBJECT
    
public:
    explicit CBarChart(BarType type, const QStringList& categories, QWidget *parent = 0);
    ~CBarChart();
    void PushData(const QList<qreal>& values, const QString& legendName = "");
    void PushData(const QList<int>& values, const QString& legendName = "");
    void Clear();
    void SetLegendVisible(bool bVisible);
    void SetTitle(const QString&);
    void SetTitleFont(const QFont &font);
    void SetValueAxisInteger(bool isInteger);

private:
    void InitCharUI(BarType type, const QStringList& categories);
    void UpdateBarSeries(const QList<QBarSet*>& barSetList);
    void UpdateValueAxisRange();

private:
    QAbstractBarSeries* m_pBarSeries;
    QChart* m_pChartModel;
    QChartView* m_pChartView;
    QValueAxis* m_pAxisVal;
    QGridLayout m_GridLayout;
    bool m_bValueAxisIsInteger;
};
#endif // BarChart_h__