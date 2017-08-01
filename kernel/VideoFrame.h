#ifndef VideoFrame_h__
#define VideoFrame_h__

#include <opencv2/core/core.hpp>
#include <QImage>
#include <QSharedPointer>

/*!
    This class handle the life cycle of the frame data.
    In addition, provide adapter for QImage & Mat data type.
*/

class CVideoFrame
{
    enum EDataSrc
    {
        eNoData,
        eUCHAR,
        eQImage,
        eMat
    };
public:
    CVideoFrame();
    //! Data will be deleted at destruction when reference count is zero.
    CVideoFrame(uchar* uData, int iWidth, int iHeight);
    //! Data will not be deleted at destruction, handle life cycle by outside.
    CVideoFrame(QImage& src);
    //! Data will not be deleted at destruction, handle life cycle by outside.
    CVideoFrame(cv::Mat& src);
    ~CVideoFrame();

    static CVideoFrame CopyFromMat(const cv::Mat& src);

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

    QImage m_qImgData;
    cv::Mat m_cvMatData;
    QSharedPointer<uchar> m_pData;

    unsigned int m_height;
    unsigned int m_width;
};
#endif // VideoFrame_h__