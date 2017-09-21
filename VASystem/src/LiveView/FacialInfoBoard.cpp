#include "FacialInfoBoard.h"

CFacialInfoBoard::CFacialInfoBoard(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
}

CFacialInfoBoard::~CFacialInfoBoard()
{

}

void CFacialInfoBoard::PushData(CImageAdaptor img, const QList<qreal>& values)
{
    m_ui.filmView->PushData(img, values);
}

