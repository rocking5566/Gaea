#include "PlayerWidget.h"
#include <QInputDialog>
#include "stream/PlayerCtrl.h"
#include "VideoFrame.h"
#include "util/Util.h"
#include "opencv2/opencv.hpp"

CPlayerWidget::CPlayerWidget(CPlayerCtrl* pPlayerCtrl, QWidget *parent)
    : QWidget(parent)
    , m_pPlayerCtrl(pPlayerCtrl)
    , m_id(-1)
{
    m_ui.setupUi(this);
    connect(m_ui.btnAttach, SIGNAL(clicked()), this, SLOT(OnAttachStream()));
    connect(m_ui.btnDetach, SIGNAL(clicked()), this, SLOT(OnAttachStream()));

}

CPlayerWidget::~CPlayerWidget()
{
    OnDetachStream();
}

void CPlayerWidget::OnAttachStream()
{
    m_id = m_ui.leStreamID->text().toInt();
    m_pPlayerCtrl->AttachStream(m_id, playerCallback, this);
}

void CPlayerWidget::OnDetachStream()
{
    m_pPlayerCtrl->DetachStream(m_id, this);
}

void CPlayerWidget::playerCallback(void *_this, int id, CVideoFrame frame)
{
    CPlayerWidget* This = (CPlayerWidget*)_this;
    This->m_ui.RenderWidget->Render(frame);
}

