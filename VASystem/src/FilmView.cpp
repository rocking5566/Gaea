#include "FilmView.h"
#include "RenderWidget.h"

CFilmView::CFilmView(QWidget *parent, int rowCount, int colCount)
    : QWidget(parent)
    , m_iRowCount(rowCount)
    , m_iColCount(colCount)
    , m_curIndex(0)
{
    m_GridLayout.setSpacing(10);
    m_GridLayout.setMargin(0);
    setLayout(&m_GridLayout);

    for (int r = 0; r < rowCount; ++r)
    {
        for (int c = 0; c < colCount; ++c)
        {
            CRenderWidget* pRenderWidget = new CRenderWidget(this);
            m_GridLayout.addWidget(pRenderWidget, r, c);
        }
    }
}

CFilmView::~CFilmView()
{

}

void CFilmView::PushImage(CVideoFrame img)
{
    int row = m_curIndex / m_iColCount;
    int col = m_curIndex % m_iColCount;
    InsertImage(img, row, col);
    m_curIndex = (m_curIndex + 1) % (m_iRowCount * m_iColCount);
}

void CFilmView::InsertImage(CVideoFrame img, int row, int col)
{
    if (row < m_iRowCount && col < m_iColCount)
    {
        CRenderWidget* pRenderWidget = dynamic_cast<CRenderWidget*>(m_GridLayout.itemAtPosition(row, col)->widget());
        pRenderWidget->Render(img);
    }
}
