#include "RtspStream.h"
#include "util/BufPoolMgr.h"
#include "util/Util.h"

using namespace std;

CRtspStream::CRtspStream()
    : m_vlcInstance(NULL)
    , m_vlcMediaPlayer(NULL)
    , m_pvlcMedia(NULL)
    , m_CbDecodeVideo(NULL)
    , m_vctx(NULL)
{
    char const* vlc_args[] =
    {
        "-I",
        "dummy",
        "--ignore-config",
    };

    m_vlcInstance = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    m_vlcMediaPlayer = libvlc_media_player_new(m_vlcInstance);
    libvlc_video_set_callbacks(m_vlcMediaPlayer, VideoLockCallback, VideoUnlockCallback, VideoDisplayCallback, this);
    memset (&m_profile, 0, sizeof(SVideoProfile));
}

CRtspStream::~CRtspStream()
{
    libvlc_media_release(m_pvlcMedia);
    libvlc_media_player_stop(m_vlcMediaPlayer);
    libvlc_media_player_release(m_vlcMediaPlayer);
    libvlc_release(m_vlcInstance);
}

void CRtspStream::SetUrl(const char* sUrl)
{
    if (m_pvlcMedia != NULL)
    {
        libvlc_media_release(m_pvlcMedia);
    }

    m_pvlcMedia = libvlc_media_new_location(m_vlcInstance, sUrl);
    libvlc_media_player_set_media(m_vlcMediaPlayer, m_pvlcMedia);
}

void CRtspStream::Play()
{
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);

    if (state == libvlc_Playing)
    {
        return;
    }

    libvlc_media_player_play(m_vlcMediaPlayer);

    // [workaround]: I don't know how to change format (libvlc_video_set_format) after playing...
    // reconnect the stream
    if (WaitConnection() && TestAndGetVlcTrack())
    {
        libvlc_media_player_stop(m_vlcMediaPlayer);
        libvlc_video_set_format(m_vlcMediaPlayer, "RV32", m_profile.m_width, m_profile.m_height, m_profile.m_width << 2);
        libvlc_media_player_play(m_vlcMediaPlayer);
    }
}

void CRtspStream::Pause()
{
    libvlc_media_player_pause(m_vlcMediaPlayer);
}

void CRtspStream::Stop()
{
    libvlc_media_player_stop(m_vlcMediaPlayer);
}

void CRtspStream::RegisterDecodeVideoCallback(DecodeVideoCb videoCb, void* vctx)
{
    m_CbDecodeVideo = videoCb;
    m_vctx = vctx;
}

void CRtspStream::UnRegisterDecodeVideoCallback()
{
    m_CbDecodeVideo = NULL;
    m_vctx = NULL;
}

bool CRtspStream::TestAndGetVlcTrack()
{
    libvlc_media_track_t **tracks = NULL;
    bool bFindResolution = false;
    int iTestNum = 0;

    while (!bFindResolution)
    {
        if (iTestNum++ > 200)
        {
            break;
        }

        unsigned tracksCount = libvlc_media_tracks_get(m_pvlcMedia, &tracks);

        if (tracks != NULL)
        {
            for (unsigned i = 0; i < tracksCount; i++)
            {
                if (tracks[i]->i_type == libvlc_track_video
                    && tracks[i]->video->i_height != 0
                    && tracks[i]->video->i_width != 0)
                {
                    m_profile.m_width = tracks[i]->video->i_width;
                    m_profile.m_height = tracks[i]->video->i_height;
                    bFindResolution = true;
                    break;
                }
            }
        }

        libvlc_media_tracks_release(tracks, tracksCount);
        MSleep(100);
    }

    return bFindResolution;
}

bool CRtspStream::WaitConnection()
{
    libvlc_state_t state = libvlc_media_player_get_state(m_vlcMediaPlayer);
    int waitCount = 0;


    while (state == libvlc_NothingSpecial || state == libvlc_Opening)
    {
        if (waitCount++ > 200)
        {
            break;
        }

        state = libvlc_media_player_get_state(m_vlcMediaPlayer);
        MSleep(100);
    }

    if (state == libvlc_NothingSpecial || state == libvlc_Opening || state == libvlc_Error)
    {
        return false;
    }

    return true;
}

void* CRtspStream::VideoLockCallback(void *opaque, void **planes)
{
    Q_UNUSED(opaque);
    Q_UNUSED(planes);

    CRtspStream* This = (CRtspStream*)opaque;
    int iWidth = This->m_profile.m_width;
    int iHeight = This->m_profile.m_height;

    if (This->m_CbDecodeVideo)
    {
        *planes = CBufPoolMgr::GetSingleTon()->Alloc((iWidth * iHeight) << 2);
    }
    else
    {
        *planes = NULL;
    }
    return *planes;
}

void CRtspStream::VideoUnlockCallback(void *opaque, void *picture, void *const *planes)
{
    // TODO
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    CRtspStream* This = (CRtspStream*)opaque;

    if (This->m_CbDecodeVideo && picture != NULL)
    {
        CVideoFrame frame((uchar*) picture, This->m_profile.m_width, This->m_profile.m_height);
        This->m_CbDecodeVideo(This->m_vctx, frame);
    }
}

void CRtspStream::VideoDisplayCallback(void *opaque, void *picture)
{
    Q_UNUSED(opaque);
    Q_UNUSED(picture);
}


