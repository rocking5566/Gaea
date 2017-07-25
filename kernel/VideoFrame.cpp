#include "VideoFrame.h"

using namespace cv;

CVideoFrame::CVideoFrame()
    : m_width(0)
    , m_height(0)
    , m_pData(NULL)
    , m_dataType(eNoData)
{

}

CVideoFrame::CVideoFrame(uchar* uData, int iWidth, int iHeight)
    : m_width(iWidth)
    , m_height(iHeight)
    , m_pData(uData)
    , m_dataType(eUCHAR)
{

}

CVideoFrame::CVideoFrame(QImage& src)
    : m_width(src.width())
    , m_height(src.height())
    , m_pData(NULL)
    , m_qKeepRefCount(src)
    , m_dataType(eQImage)
{

}

CVideoFrame::CVideoFrame(cv::Mat& src)
    : m_width(src.cols)
    , m_height(src.rows)
    , m_pData(NULL)
    , m_cvKeepRefCount(src)
    , m_dataType(eMat)
{

}

CVideoFrame::~CVideoFrame()
{

}

uchar* CVideoFrame::Data()
{
    switch(m_dataType)
    {
    case eUCHAR:
        return m_pData.data();
    case eQImage:
        return const_cast<uchar*>(m_qKeepRefCount.constBits());     // Avoid deep copy
    case eMat:
        return m_cvKeepRefCount.data;
    }
}

Mat CVideoFrame::ToMat()
{
    return Mat(cv::Size(m_width, m_height), CV_8UC4, Data());
}

QImage CVideoFrame::ToQImage()
{
    return QImage(Data(), m_width, m_height, QImage::Format_ARGB32);
}

