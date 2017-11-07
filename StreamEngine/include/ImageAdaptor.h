/**
 *  @author Rocking Lai
 *  @version 1.0 2017.11.08
 *  @date    2017.11.08
 *  @section DESCRIPTION
 *
 *  This class handle the life cycle of the frame data.
 *  In addition, provide adapter for QImage & Mat data type.
 */


#ifndef ImageAdaptor_h__
#define ImageAdaptor_h__

#include <opencv2/core/core.hpp>
#include <QImage>
#include <QSharedPointer>
#include "Util.h"

class GAEA_EXPORTS CImageAdaptor
{
    enum EDataSrc
    {
        eNoData,
        eUCHAR,
        eQImage,
        eMat
    };

public:
    enum Format
    {
        Format_Invalid,
        Format_ARGB32   // (0xAARRGGBB)
    };

    CImageAdaptor();
    //! Data will be deleted at destruction when reference count is zero.
    //! Only support 32-bit ARGB format (0xAARRGGBB).
    CImageAdaptor(uchar* uData, int iWidth, int iHeight, Format format);
    //! Data will not be deleted at destruction, handle life cycle by outside.
    CImageAdaptor(QImage& src);
    //! Data will not be deleted at destruction, handle life cycle by outside.
    CImageAdaptor(cv::Mat& src);
    ~CImageAdaptor();

    static CImageAdaptor CopyFromMat(const cv::Mat& src);

    inline unsigned int Height()
    {
        return m_height;
    }

    inline unsigned int Width()
    {
        return m_width;
    }

    uchar* Data();
    cv::Mat ToMat();
    QImage ToQImage();

private:
    EDataSrc m_dataType;
    Format m_uCharFormat;

    QImage m_qImgData;
    cv::Mat m_cvMatData;
    QSharedPointer<uchar> m_pData;

    unsigned int m_height;
    unsigned int m_width;
};
#endif // ImageAdaptor_h__
