#ifndef RtspStream_h__
#define RtspStream_h__

#include <QString>
#include "vlc/vlc.h"
#include "StreamClient.h"

/*!
    This class is LibVLC wrapper, use libVlc to handle RTSP protocol and video decoder.
    Replace with Live555 and ffmpeg in the future.
*/
class CRtspStream : public CStreamClient
{
public:
    CRtspStream();
    virtual ~CRtspStream();

    virtual void SetUrl(const char* sUrl);
    virtual void Play();
    virtual void Pause();
    virtual void Stop();

private:
    bool TestAndGetVlcTrack();
    bool WaitConnection();

    //libvlc callback
    static void* VideoLockCallback(void *opaque, void **planes);
    static void VideoUnlockCallback(void *opaque, void *picture, void *const *planes);
    static void VideoDisplayCallback(void *opaque, void *picture);

private:
    libvlc_instance_t* m_vlcInstance;
    libvlc_media_player_t* m_vlcMediaPlayer;
    libvlc_media_t* m_pvlcMedia;
};
#endif // RtspStream_h__
