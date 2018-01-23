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
    : m_maxMemberID(0)
{

}

CMemberModel::~CMemberModel()
{

}

int CMemberModel::AddMember(const SMemberProperty& rMember)
{
    // [TODO] update database
    m_mapIdtoMember[m_maxMemberID] = rMember;
    return m_maxMemberID++;
}

void CMemberModel::RemoveMember(int memberId)
{
    // [TODO] update database
    m_mapIdtoMember.remove(memberId);
}

bool CMemberModel::EditName(int memberId, const QString& rName)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(memberId);

    if (bExist)
    {
        m_mapIdtoMember[memberId].m_name = rName;
    }

    return bExist;
}

bool CMemberModel::EditGender(int memberId, EGender gender)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(memberId);

    if (bExist)
    {
        m_mapIdtoMember[memberId].m_gender = gender;
    }

    return bExist;
}

bool CMemberModel::EditAge(int memberId, int age)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(memberId);

    if (bExist)
    {
        m_mapIdtoMember[memberId].m_age = age;
    }

    return bExist;
}

bool CMemberModel::EditVideoFrame(int memberId, const QList<CImageAdaptor>& rFacePictures)
{
    // [TODO] update database
    bool bExist = m_mapIdtoMember.contains(memberId);

    if (bExist)
    {
        m_mapIdtoMember[memberId].m_facePictures = rFacePictures;
    }

    return bExist;
}

bool CMemberModel::GetMember(int memberId, SMemberProperty& rMember) const
{
    // [TODO] Get data from Database
    bool bExist = m_mapIdtoMember.contains(memberId);

    if (bExist)
    {
        rMember = m_mapIdtoMember[memberId];
    }

    return bExist;
}


