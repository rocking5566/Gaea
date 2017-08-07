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
    connect(m_ui.btnConnect, SIGNAL(clicked()), this, SLOT(OnConnectStream()));

}

CPlayerWidget::~CPlayerWidget()
{
    m_pPlayerCtrl->DetachStream(m_id, this);
    m_pPlayerCtrl->DisConnect(m_id, false);
}

void CPlayerWidget::OnConnectStream()
{
    SConnectInfo info;

    if (m_ui.rbRtsp->isChecked())
    {
        bool bOk = false;

        info.m_type = eRTSP;
        info.m_sUrl = QInputDialog::getText(this, tr("Open RTSP"),
            tr("RTSP url:"), QLineEdit::Normal,
            "rtsp://127.0.0.1:8554/test.mkv", &bOk);
    }

    m_id = m_pPlayerCtrl->Connect(info);
    m_pPlayerCtrl->AttachStream(m_id, playerCallback, this);
}

void CPlayerWidget::playerCallback(void *_this, int id, CVideoFrame frame)
{
    CPlayerWidget* This = (CPlayerWidget*)_this;
    This->m_ui.RenderWidget->Render(frame);
}

