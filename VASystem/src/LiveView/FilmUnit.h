#ifndef FilmUnit_h__
#define FilmUnit_h__

#include <QGridLayout>
#include <QWidget>
#include "ImageAdaptor.h"

class CBarChart;
class CRenderWidget;

class CFilmUnit : public QWidget
{
    Q_OBJECT

public:
    explicit CFilmUnit(QWidget *parent = 0);
    ~CFilmUnit();
    void RenderData(CImageAdaptor img, const QList<qreal>& values);

private:
    QGridLayout m_GridLayout;
    CRenderWidget* m_pRenderWidget;
    CBarChart* m_pBarChart;
};
#endif // FilmUnit_h__
