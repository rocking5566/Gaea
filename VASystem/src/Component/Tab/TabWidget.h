#ifndef TabWidget_h__
#define TabWidget_h__

#include <QTabWidget>

class CTabEntity;
class CTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit CTabWidget(QWidget *parent = 0);
    ~CTabWidget();

private slots:
    void OnCurrentChanged(int index);

private:
    CTabEntity* m_pPreviousTab;
};
#endif // TabWidget_h__
