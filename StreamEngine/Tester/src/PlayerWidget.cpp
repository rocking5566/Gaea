#include "PlayerWidget.h"
#include <QInputDialog>
#include "PlayerCtrl.h"
#include "VideoFrame.h"
#include "Util.h"
#include "opencv2/opencv.hpp"

CPlayerWidget::CPlayerWidget(CPlayerCtrl* pPlayerCtrl, QWidget *parent)
    : QWidget(parent)
    , m_pPlayerCtrl(pPlayerCtrl)
{
    m_ui.setupUi(this);
    connect(m_ui.btnAttach, SIGNAL(clicked()), this, SLOT(OnAttachStream()));
    connect(m_ui.btnDetachAll, SIGNAL(clicked()), this, SLOT(OnDetachAllStream()));

}

CPlayerWidget::~CPlayerWidget()
{
    OnDetachAllStream();
}

void CPlayerWidget::OnAttachStream()
{
    if (!m_ui.leStreamID->text().isEmpty())
    {
        int id = m_ui.leStreamID->text().toInt();
        m_pPlayerCtrl->AttachStream(id, playerCallback, this);
        m_idList << id;
    }
}

void CPlayerWidget::OnDetachAllStream()
{
    foreach (int id, m_idList)
    {
        m_pPlayerCtrl->DetachStream(id, this);
    }
}

void CPlayerWidget::playerCallback(void *_this, int id, CVideoFrame frame)
{
    Q_UNUSED(id);
    CPlayerWidget* This = (CPlayerWidget*)_this;
    This->m_ui.RenderWidget->Render(frame);
}

