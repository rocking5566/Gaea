#include "FacialInfoBoard.h"

CFacialInfoBoard::CFacialInfoBoard(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
}

CFacialInfoBoard::~CFacialInfoBoard()
{

}

void CFacialInfoBoard::PushImage(CImageAdaptor img)
{
    m_ui.filmView->PushImage(img);
}

