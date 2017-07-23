#include "VideoFrame.h"

using namespace cv;

CVideoFrame::CVideoFrame()
    : m_width(0)
    , m_height(0)
    , m_pData(NULL)
{

}

CVideoFrame::CVideoFrame(QImage& src)
    : m_width(src.width())
    , m_height(src.height())
    , m_pData(src.bits())
{

}

CVideoFrame::CVideoFrame(cv::Mat& src)
    : m_width(src.cols)
    , m_height(src.rows)
    , m_pData(src.data)
{

}

CVideoFrame::~CVideoFrame()
{

}

Mat CVideoFrame::ToMat()
{
    return Mat(cv::Size(m_width, m_height), CV_8UC4, (void*)m_pData);
}

QImage CVideoFrame::ToQImage()
{
    return QImage(m_pData, m_width, m_height, QImage::Format_ARGB32);
}

