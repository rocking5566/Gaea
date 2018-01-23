#include "SysConfigWidget.h"

CSysConfigWidget::CSysConfigWidget(QWidget *parent /*= 0*/)
    : CTabEntity(parent)
{
    m_ui.setupUi(this);
}

CSysConfigWidget::~CSysConfigWidget()
{
}

void CSysConfigWidget::Enter()
{
    // [TODO] Load data from model
}

void CSysConfigWidget::Leave()
{
    // [TODO] Save data to model
}
