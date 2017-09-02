#include "FaceDataBase.h"

CFaceDataBase* CFaceDataBase::sm_Instance = NULL;

CFaceDataBase* CFaceDataBase::GetSingleTon()
{
    if (sm_Instance == NULL)
    {
        sm_Instance = new CFaceDataBase();
    }

    return sm_Instance;
}

CFaceDataBase::CFaceDataBase()
    : m_maxID(0)
{

}

CFaceDataBase::~CFaceDataBase()
{

}

int CFaceDataBase::AddFace(const SFaceEntity& rEnt)
{
    // [TODO] update database
    m_mapIdtoFace[m_maxID] = rEnt;
    return m_maxID++;
}

void CFaceDataBase::RemoveFace(int id)
{
    // [TODO] update database
    m_mapIdtoFace.remove(id);
}

bool CFaceDataBase::EditName(int id, const QString& rName)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_name = rName;
    }

    return bExist;
}

bool CFaceDataBase::EditGender(int id, EGender gender)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_gender = gender;
    }

    return bExist;
}

bool CFaceDataBase::EditAge(int id, int age)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_age = age;
    }

    return bExist;
}

bool CFaceDataBase::EditVideoFrame(int id, const QList<CVideoFrame>& rFacePictures)
{
    // [TODO] update database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        m_mapIdtoFace[id].m_facePictures = rFacePictures;
    }

    return bExist;
}

bool CFaceDataBase::GetFace(int id, SFaceEntity& rEnt) const
{
    // [TODO] Get data from Database
    bool bExist = m_mapIdtoFace.contains(id);

    if (bExist)
    {
        rEnt = m_mapIdtoFace[id];
    }

    return bExist;
}

QStringList CFaceDataBase::GetAllEntityName() const
{
    // [TODO] Get data from Database
    QStringList ret;
    auto iter = m_mapIdtoFace.constBegin();
    while (iter != m_mapIdtoFace.constEnd())
    {
        ret << iter.value().m_name;
        ++iter;
    }

    return ret;
}

