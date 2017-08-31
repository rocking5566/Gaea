#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include "ui_HomeWindow.h"

class CHomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CHomeWindow(QWidget *parent = 0);
    ~CHomeWindow();

private:
    Ui::HomeWindow m_ui;

};

#endif // HOMEWINDOW_H
