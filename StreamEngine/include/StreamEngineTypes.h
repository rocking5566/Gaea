#ifndef StreamEngineTypes_h__
#define StreamEngineTypes_h__

#include <QString>

enum EConnectType
{
    eNone,
    eLocalFile,
    eWebCam,
    eRTSP,
};

struct SConnectInfo
{
    SConnectInfo()
        : m_type(eNone)
        , m_iWebCamDeviceID(0)
    {}

    EConnectType m_type;
    QString m_sUrl;             // eLocalFile or eRTSP
    int m_iWebCamDeviceID;      // eWebCam
};
#endif // StreamEngineTypes_h__
