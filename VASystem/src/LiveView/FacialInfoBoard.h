#ifndef FacialInfoWidget_h__
#define FacialInfoWidget_h__

#include <QWidget>
#include "ImageAdaptor.h"
#include "ui_FacialInfoBoard.h"

class CFacialInfoBoard : public QWidget
{
    Q_OBJECT

public:
    explicit CFacialInfoBoard(QWidget *parent = 0);
    ~CFacialInfoBoard();

    void PushData(CImageAdaptor img, const QList<qreal>& values);

private:
    Ui::FacialInfoBoard m_ui;
};
#endif // FacialInfoWidget_h__
