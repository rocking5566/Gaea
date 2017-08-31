#ifndef ConfigDeviceWidget_h__
#define ConfigDeviceWidget_h__

#include <QMainWindow>
#include "ui_ConfigDeviceWidget.h"

class CConfigDeviceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CConfigDeviceWidget(QWidget *parent = 0);
    ~CConfigDeviceWidget();

private:
    Ui::ConfigDeviceWidget m_ui;

};
#endif // ConfigDeviceWidget_h__
