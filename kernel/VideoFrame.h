#include <opencv2/core/core.hpp>
#include <QImage>
#include <QSharedPointer>

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
    CVideoFrame(uchar* uData, int iWidth, int iHeight);
    CVideoFrame(QImage& src);
    CVideoFrame(cv::Mat& src);
    ~CVideoFrame();


    uchar* Data();
    cv::Mat ToMat();
    QImage ToQImage();

private:
    //=========================================================================
    // QImage & Mat has its own ref count.
    // If data come from QImage or Mat, let them keep life cycle of frame data
    QImage m_qKeepRefCount;
    cv::Mat m_cvKeepRefCount;
    //=========================================================================

    EDataSrc m_dataType;
    unsigned int m_height;
    unsigned int m_width;
    QSharedPointer<uchar> m_pData;
};