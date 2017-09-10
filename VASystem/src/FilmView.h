#ifndef FilmView_h__
#define FilmView_h__

#include <QGridLayout>
#include <QWidget>
#include "VideoFrame.h"

class CFilmView : public QWidget
{
    Q_OBJECT

public:
    explicit CFilmView(QWidget *parent = 0, int rowCount = 1, int colCount = 5);
    ~CFilmView();

    void PushImage(CVideoFrame img);
    void InsertImage(CVideoFrame img, int row, int col);

private:
    QGridLayout m_GridLayout;
    int m_iRowCount;
    int m_iColCount;
    int m_curIndex; // 0 ~ col * row
};
#endif // FilmView_h__
