#ifndef PlayerWidget_h__
#define PlayerWidget_h__

#include <QWidget>
#include "ImageAdaptor.h"
#include "ui_PlayerWidget.h"

class CPlayerCtrl;

class CPlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CPlayerWidget(CPlayerCtrl* pPlayerCtrl, QWidget *parent = 0);
    virtual ~CPlayerWidget();

private slots:
    void OnAttachStream();
    void OnDetachAllStream();

private:
    static void playerCallback(void *_this, int id, CImageAdaptor frame);

private:
    Ui::PlayerWidget m_ui;
    CPlayerCtrl* m_pPlayerCtrl;
    QList<int> m_idList;
};
#endif // PlayerWidget_h__