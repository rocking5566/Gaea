#ifndef PlayerWidget_h__
#define PlayerWidget_h__

#include <QWidget>
#include "VideoFrame.h"
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
    void OnDetachStream();

private:
    static void playerCallback(void *_this, int id, CVideoFrame frame);

private:
    Ui::PlayerWidget m_ui;
    CPlayerCtrl* m_pPlayerCtrl;
    int m_id;
};
#endif // PlayerWidget_h__