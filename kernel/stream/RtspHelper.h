#ifndef RtspHelper_h__
#define RtspHelper_h__

#include <QString>

class CRtspHelper
{
public:
    CRtspHelper();
    ~CRtspHelper();

    void SetUrl(const char* sUrl);

private:
    QString m_sUrl;
};
#endif // RtspHelper_h__