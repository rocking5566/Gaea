#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QMainWindow>
#include "ui_HomeWindow.h"

class CPlayerCtrl;
class CPlayerWidget;
class CConnectionListDock;

class CHomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CHomeWindow(QWidget *parent = 0);
    ~CHomeWindow();

private slots:
    void OnAddPlayer();
    void OnRemovePlayer();

private:
    Ui::HomeWindow m_ui;
    CPlayerCtrl* m_pPlayerCtrl;

    CConnectionListDock* m_pConnectionListDock;
    QList<CPlayerWidget*> m_PlayerWidgetList;
};

#endif // HOMEWINDOW_H
