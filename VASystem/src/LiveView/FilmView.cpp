#include "FilmView.h"
#include "RenderWidget.h"
#include "FilmUnit.h"

CFilmView::CFilmView(QWidget *parent, int rowCount, int colCount)
    : QWidget(parent)
    , m_iRowCount(rowCount)
    , m_iColCount(colCount)
    , m_curIndex(0)
    , m_GridLayout(this)
{
    m_GridLayout.setSpacing(10);
    m_GridLayout.setMargin(0);
    setLayout(&m_GridLayout);

    for (int r = 0; r < rowCount; ++r)
    {
        for (int c = 0; c < colCount; ++c)
        {
            CFilmUnit* pFilmWidget = new CFilmUnit(this);
            m_GridLayout.addWidget(pFilmWidget, r, c);
        }
    }
}

CFilmView::~CFilmView()
{

}

void CFilmView::PushData(CImageAdaptor img, const QList<qreal>& values)
{
    int row = m_curIndex / m_iColCount;
    int col = m_curIndex % m_iColCount;
    InsertData(img, values, row, col);
    m_curIndex = (m_curIndex + 1) % (m_iRowCount * m_iColCount);
}

void CFilmView::InsertData(CImageAdaptor img, const QList<qreal>& values, int row, int col)
{
    if (row < m_iRowCount && col < m_iColCount)
    {
        CFilmUnit* pFilmWidget = dynamic_cast<CFilmUnit*>(m_GridLayout.itemAtPosition(row, col)->widget());
        pFilmWidget->RenderData(img, values);
    }
}
