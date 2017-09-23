#include "BarChart.h"
#include "Util.h"

CBarChart::CBarChart(BarType type, const QStringList& categories, QWidget *parent /*= 0*/)
    : QWidget(parent)
    , m_pBarSeries(NULL)
    , m_GridLayout(this)
    , m_pChartModel(new QChart)
    , m_pChartView(new QChartView)
    , m_pAxisVal(new QValueAxis)
{
    m_GridLayout.setSpacing(10);
    m_GridLayout.setMargin(0);
    setLayout(&m_GridLayout);
    m_GridLayout.addWidget(m_pChartView);

    InitCharUI(type, categories);
}

void CBarChart::InitCharUI(BarType type, const QStringList& categories)
{
    m_pChartModel->setAnimationOptions(QChart::SeriesAnimations);

    m_pChartModel->legend()->setVisible(false);
    m_pChartModel->legend()->setAlignment(Qt::AlignBottom);

    m_pChartView->setRenderHint(QPainter::Antialiasing);
    m_pChartView->setChart(m_pChartModel);

    QBarCategoryAxis *pAxisCategory = new QBarCategoryAxis();
    pAxisCategory->append(categories);

    switch (type)
    {
    case eVertical:
        m_pBarSeries = new QBarSeries();
        m_pChartModel->setAxisX(pAxisCategory, m_pBarSeries);
        m_pChartModel->setAxisY(m_pAxisVal, m_pBarSeries);
        break;
    case eHorizontal:
        m_pBarSeries = new QHorizontalBarSeries();
        m_pChartModel->setAxisX(m_pAxisVal, m_pBarSeries);
        m_pChartModel->setAxisY(pAxisCategory, m_pBarSeries);
        break;
    }

    m_pChartModel->addSeries(m_pBarSeries);
}

CBarChart::~CBarChart()
{
    SAFE_DELETE(m_pChartView);
}

void CBarChart::PushData(const QList<qreal>& values, const QString& legendName)
{
    QBarSet* pSet = new QBarSet(legendName);
    pSet->append(values);
    UpdateBarSeries({pSet});
}

void CBarChart::PushData(const QList<int>& values, const QString& legendName /*= ""*/)
{
    QList<qreal> doubleValues;

    foreach (int i, values)
    {
        doubleValues << i;
    }

    PushData(doubleValues, legendName);
}

void CBarChart::UpdateBarSeries(const QList<QBarSet*>& barSetList)
{
    m_pChartModel->removeSeries(m_pBarSeries);
    m_pBarSeries->append(barSetList);
    m_pChartModel->addSeries(m_pBarSeries);
    UpdateValueAxisRange();
}

void CBarChart::UpdateValueAxisRange()
{
    const QList<QBarSet*>& barSetList = m_pBarSeries->barSets();

    int max = 0;
    foreach(QBarSet* pBarSet, barSetList)
    {
        for (int i = 0; i < pBarSet->count(); ++i)
        {
            max = pBarSet->at(i) > max ? pBarSet->at(i) : max;
        }
    }

    m_pAxisVal->setMax(max);
}

void CBarChart::SetLegendVisible(bool bVisible)
{
    m_pChartModel->legend()->setVisible(bVisible);
}

void CBarChart::Clear()
{
    m_pChartModel->removeSeries(m_pBarSeries);
    m_pBarSeries->clear();
    m_pChartModel->addSeries(m_pBarSeries);
}

void CBarChart::SetTitle(const QString& title)
{
    m_pChartModel->setTitle(title);
}

void CBarChart::SetTitleFont(const QFont &font)
{
    m_pChartModel->setTitleFont(font);
}
