#include <opencv2/core/core.hpp>
#include <QImage>

class CVideoFrame
{
public:
    CVideoFrame();
    CVideoFrame(QImage& src);
    CVideoFrame(cv::Mat& src);
    ~CVideoFrame();

    cv::Mat ToMat();
    QImage ToQImage();

private:
    unsigned int m_height;
    unsigned int m_width;
    uchar* m_pData;
};