#include "MemberModel.h"

CMemberModel* CMemberModel::sm_Instance = NULL;

CMemberModel* CMemberModel::GetSingleTon()
{
    if (sm_Instance == NULL)
    {
        sm_Instance = new CMemberModel();
    }

    return sm_Instance;
}

CMemberModel::CMemberModel()
    : m_maxID(0)
{

}

CMemberModel::~CMemberModel()
{

}

int CMemberModel::AddMember(const SMemberProperty& rMember)
{
    // [TODO] update database
    m_mapIdtoMember[m_maxID] = rMember;
    return m_maxID++;
}

void CMemberModel::RemoveMember(int id)
{
    // [TODO] update database
    m_mapIdtoMember.remove(id);
}

bool CMemberModel::EditName(int id, const QString& rName)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(id);

    if (bExist)
    {
        m_mapIdtoMember[id].m_name = rName;
    }

    return bExist;
}

bool CMemberModel::EditGender(int id, EGender gender)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(id);

    if (bExist)
    {
        m_mapIdtoMember[id].m_gender = gender;
    }

    return bExist;
}

bool CMemberModel::EditAge(int id, int age)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(id);

    if (bExist)
    {
        m_mapIdtoMember[id].m_age = age;
    }

    return bExist;
}

bool CMemberModel::EditVideoFrame(int id, const QList<CImageAdaptor>& rFacePictures)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(id);

    if (bExist)
    {
        m_mapIdtoMember[id].m_facePictures = rFacePictures;
    }

    return bExist;
}

bool CMemberModel::GetMember(int id, SMemberProperty& rMember) const
{
    // [TODO] Get data from Database
    bool bExist = m_mapIdtoMember.contains(id);

    if (bExist)
    {
        rMember = m_mapIdtoMember[id];
    }

    return bExist;
}


