#ifndef CStreamClient_h__
#define CStreamClient_h__

#include "VideoFrame.h"

typedef void(*DecodeVideoCb)(void *pListener, CVideoFrame frame);

class CStreamClient
{
public:
    CStreamClient();
    virtual ~CStreamClient();

    virtual void SetUrl(const char* sUrl) = 0;
    virtual void Play() = 0;
    virtual void Pause() = 0;
    virtual void Stop() = 0;

    void RegisterDecodeVideoCallback(DecodeVideoCb videoCb, void* pListener);
    void UnRegisterDecodeVideoCallback();

protected:
    DecodeVideoCb m_CbDecodeVideo;
    void* m_pListener;
};
#endif // CStreamClient_h__