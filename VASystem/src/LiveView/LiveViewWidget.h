#include <QWidget>
#include "ui_LiveViewWidget.h"

class CLiveViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CLiveViewWidget(QWidget *parent = 0);
    ~CLiveViewWidget();

private:
    Ui::LiveViewWidget m_ui;
};
