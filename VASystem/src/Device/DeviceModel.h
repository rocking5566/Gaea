#ifndef DeviceConfig_h__
#define DeviceConfig_h__
#include <QString>
#include <QMap>

struct SDeviceProperty
{
    SDeviceProperty()
    {
    }

    SDeviceProperty(const QString& rName, const QString& rUrl)
        : m_name(rName)
        , m_url(rUrl)
    {
    }

    QString m_name;
    QString m_url;
};

class CDeviceModel
{
public:
    static CDeviceModel* GetSingleTon();
    int AddDevice(const SDeviceProperty& rDev);   // return id
    void RemoveDevice(int id);
    bool EditDevice(int id, const SDeviceProperty& rDev);

    bool GetDevice(int id, SDeviceProperty& rMember) const;

private:
    explicit CDeviceModel();
    ~CDeviceModel();
    static CDeviceModel* sm_Instance;

    int m_maxID;
    QMap<int, SDeviceProperty> m_mapIdtoDevice;
};
#endif // DeviceConfig_h__