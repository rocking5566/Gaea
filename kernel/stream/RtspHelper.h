#ifndef RtspHelper_h__
#define RtspHelper_h__

#include <QString>
#include "vlc/vlc.h"

typedef void *(*DecodeVideoCb)(void *context, void *frame);

struct SVideoProfile
{
    unsigned int m_bitrate;
    unsigned int m_height;
    unsigned int m_width;
};

class CRtspHelper
{
public:
    CRtspHelper();
    ~CRtspHelper();

    void SetUrl(const char* sUrl);
    void Play();
    void Pause();
    void Stop();

    void RegisterDecodeVideoCallback(DecodeVideoCb videoCb, void* vctx);

private:
    bool TestAndGetVlcTrack();
    bool WaitConnection();

    //libvlc callback
    static void* VideoLockCallback(void *opaque, void **planes);
    static void VideoUnlockCallback(void *opaque, void *picture, void *const *planes);
    static void VideoDisplayCallback(void *opaque, void *picture);

private:
    DecodeVideoCb m_CbDecodeVideo;
    void* m_vctx;

    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_pvlcMedia;
    SVideoProfile m_profile;
};
#endif // RtspHelper_h__