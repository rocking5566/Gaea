#include "FacialInfoWidget.h"

CFacialInfoWidget::CFacialInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
}

CFacialInfoWidget::~CFacialInfoWidget()
{

}

void CFacialInfoWidget::PushImage(CImageAdaptor img)
{
    m_ui.filmView->PushImage(img);
}

