#ifndef ViewPanel_h__
#define ViewPanel_h__

#include <QWidget>

class CViewPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CViewPanel(QWidget *parent = 0);
    ~CViewPanel();

};
#endif // ViewPanel_h__
