#ifndef WebCamStream_h__
#define WebCamStream_h__

#include "StreamClient.h"
#include <QThread>
#include <opencv2/opencv.hpp>

/*!
    This class is OpenCV's VideoCapture wrapper, use to capture web cam stream.
*/

class CWebCamStream : public QThread, public CStreamClient
{
    Q_OBJECT

public:
    //! Do not open same video device
    CWebCamStream(int iWebCamDeviceID);
    virtual ~CWebCamStream();

    void SetFPS(double fps);

    // WebCam does not support url
    virtual void SetUrl(const char* sUrl) {Q_UNUSED(sUrl);}
    virtual void Play();
    virtual void Pause();
    virtual void Stop();

protected:
    // Thread operation
    virtual void run();
    void StartThread();
    void StopThread();

private:
    bool m_bQuitThread;
    int m_iWebCamDeviceID;
    cv::VideoCapture m_vCap;
    double m_dFps;
};
#endif // WebCamStream_h__