#include "DeviceModel.h"

CDeviceModel* CDeviceModel::sm_Instance = NULL;

CDeviceModel* CDeviceModel::GetSingleTon()
{
    if (sm_Instance == NULL)
    {
        sm_Instance = new CDeviceModel();
    }

    return sm_Instance;
}

CDeviceModel::CDeviceModel()
    : m_maxID(0)
{

}

CDeviceModel::~CDeviceModel()
{

}

int CDeviceModel::AddDevice(const SDeviceProperty& rDev)
{
    // [TODO] update config file
    m_mapIdtoDevice[m_maxID] = rDev;
    return m_maxID++;
}

void CDeviceModel::RemoveDevice(int id)
{
    // [TODO] update config file
    m_mapIdtoDevice.remove(id);
}

void CDeviceModel::Clear()
{
    // [TODO] update config file
    m_mapIdtoDevice.clear();
}

bool CDeviceModel::EditDevice(int id, const SDeviceProperty& rDev)
{
    // [TODO] update config file
    bool bExist = m_mapIdtoDevice.contains(id);

    if (bExist)
    {
        m_mapIdtoDevice[id] = rDev;
    }

    return bExist;
}

bool CDeviceModel::GetDevice(int id, SDeviceProperty& rMember) const
{
    // [TODO] update config file
    bool bExist = m_mapIdtoDevice.contains(id);

    if (bExist)
    {
        rMember = m_mapIdtoDevice[id];
    }

    return bExist;
}

bool CDeviceModel::GetDevices(QMap<int, SDeviceProperty>& rDeviceMap) const
{
    rDeviceMap = m_mapIdtoDevice;
    return true;
}

