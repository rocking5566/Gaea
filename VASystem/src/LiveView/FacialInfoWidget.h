#ifndef FacialInfoWidget_h__
#define FacialInfoWidget_h__

#include <QWidget>
#include "ui_FacialInfoWidget.h"

class CFacialInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CFacialInfoWidget(QWidget *parent = 0);
    ~CFacialInfoWidget();

    void PushImage(CImageAdaptor img);

private:
    Ui::FacialInfoWidget m_ui;
};
#endif // FacialInfoWidget_h__
