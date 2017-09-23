#include "Tab/TabEntity.h"
#include "ui_StatisticWidget.h"

class CBarChart;

class CStatisticWidget : public CTabEntity
{
    Q_OBJECT

public:
    explicit CStatisticWidget(QWidget *parent = 0);
    ~CStatisticWidget();

    // override CTabEntity
    virtual void Enter();
    virtual void Leave();

private:
    void InitUI();
    void UpdateData();

private:
    Ui::StatisticWidget m_ui;
    CBarChart* m_pEmotionBarChart;
};
