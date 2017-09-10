#include "ImageAdaptor.h"

using namespace cv;

CImageAdaptor::CImageAdaptor()
    : m_width(0)
    , m_height(0)
    , m_pData(NULL)
    , m_dataType(eNoData)
    , m_uCharFormat(Format_Invalid)
{

}

CImageAdaptor::CImageAdaptor(uchar* uData, int iWidth, int iHeight, Format format)
    : m_width(iWidth)
    , m_height(iHeight)
    , m_pData(uData)
    , m_dataType(eUCHAR)
    , m_uCharFormat(format)
{
    // TODO - Support more image formats.
    // Only support 32-bit ARGB format (0xAARRGGBB) so far.
}

CImageAdaptor::CImageAdaptor(QImage& src)
    : m_width(src.width())
    , m_height(src.height())
    , m_pData(NULL)
    , m_qImgData(src)
    , m_dataType(eQImage)
    , m_uCharFormat(Format_Invalid)
{

}

CImageAdaptor::CImageAdaptor(cv::Mat& src)
    : m_width(src.cols)
    , m_height(src.rows)
    , m_pData(NULL)
    , m_cvMatData(src)
    , m_dataType(eMat)
    , m_uCharFormat(Format_Invalid)
{

}

CImageAdaptor::~CImageAdaptor()
{

}

CImageAdaptor CImageAdaptor::CopyFromMat(const cv::Mat& src)
{
    Mat _src = src.clone();
    return CImageAdaptor(_src);
}

uchar* CImageAdaptor::Data()
{
    switch(m_dataType)
    {
    case eUCHAR:
        return m_pData.data();
    case eQImage:
        return const_cast<uchar*>(m_qImgData.constBits());     // Avoid deep copy
    case eMat:
        return m_cvMatData.data;
    default:
        return NULL;
    }
}

Mat CImageAdaptor::ToMat()
{
    if (m_dataType == eMat)
    {
        return m_cvMatData;
    }

    return Mat(cv::Size(m_width, m_height), CV_8UC4, Data());
}

QImage CImageAdaptor::ToQImage()
{
    if (m_dataType == eQImage)
    {
        return m_qImgData;
    }

    QImage::Format format = QImage::Format_ARGB32;

    if (eMat == m_dataType)
    {
        if (CV_8UC3 == m_cvMatData.type())
        {
            // OpenCV is BGR by default.
            QImage ret(Data(), m_width, m_height, QImage::Format_RGB888);
            return ret.rgbSwapped();
        }

        switch (m_cvMatData.type())
        {
        case CV_8UC1:
            format = QImage::Format_Indexed8;
            break;
        case CV_8UC4:
            format = QImage::Format_ARGB32;
            break;
        }
    }
    else if (eUCHAR == m_dataType)
    {
        format = QImage::Format_ARGB32;
    }

    return QImage(Data(), m_width, m_height, format);
}

