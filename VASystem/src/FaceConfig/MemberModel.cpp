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

int CMemberModel::AddFace(const SMemberProperty& rMember)
{
    // [TODO] update database
    m_mapIdtoFace[m_maxID] = rMember;
    return m_maxID++;
}

void CMemberModel::RemoveFace(int id)
{
    // [TODO] update database
    m_mapIdtoFace.remove(id);
}

bool CMemberModel::EditName(int id, const QString& rName)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_name = rName;
    }

    return bExist;
}

bool CMemberModel::EditGender(int id, EGender gender)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_gender = gender;
    }

    return bExist;
}

bool CMemberModel::EditAge(int id, int age)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_age = age;
    }

    return bExist;
}

bool CMemberModel::EditVideoFrame(int id, const QList<CVideoFrame>& rFacePictures)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_facePictures = rFacePictures;
    }

    return bExist;
}

bool CMemberModel::GetFace(int id, SMemberProperty& rMember) const
{
    // [TODO] Get data from Database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        rMember = m_mapIdtoFace[id];
    }

    return bExist;
}


