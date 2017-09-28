#include "FilmUnit.h"
#include "RenderWidget.h"
#include "BarChart.h"
#include "Statistic/StatisticModel.h"
#include <QLabel>

CFilmUnit::CFilmUnit(QWidget *parent /*= 0*/)
    : QWidget(parent)
    , m_pRenderWidget(NULL)
    , m_pBarChart(NULL)
{
    m_GridLayout.setSpacing(10);
    m_GridLayout.setMargin(0);
    setLayout(&m_GridLayout);

    m_pRenderWidget = new CRenderWidget(this);
    m_pRenderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pRenderWidget->setMinimumSize(250, 250);

    QStringList emotionCategory = CStatisticModel::GetSingleTon()->GetEmotionCategory();
    m_pBarChart = new CBarChart(eHorizontal, emotionCategory, this);
    m_pBarChart->setMaximumSize(350, 250);

    m_GridLayout.addWidget(m_pRenderWidget, 0, 0);
    m_GridLayout.addWidget(m_pBarChart, 1, 0);
}

CFilmUnit::~CFilmUnit()
{
}

void CFilmUnit::RenderData(CImageAdaptor img, const QList<qreal>& values)
{
    m_pRenderWidget->Render(img);
    m_pBarChart->Clear();
    m_pBarChart->PushData(values);
}

