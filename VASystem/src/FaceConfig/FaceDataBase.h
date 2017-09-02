#ifndef FaceDataBase_h__
#define FaceDataBase_h__
#include <QString>
#include <QList>
#include <QMap>
#include "VideoFrame.h"

enum EGender
{
    eMale,
    eFemale
};

inline const char* GenderToString(EGender gender)
{
    if (gender == eMale)
        return "Male";

    return "Female";
}

inline EGender StringToGender(const QString& rSGender)
{
    if (rSGender == "Male")
        return eMale;

    return eFemale;
}

struct SFaceEntity
{
    SFaceEntity()
        : m_gender(eMale)
        , m_age(0)
    {}

    SFaceEntity(const QString& rName, EGender gender, int age)
        : m_name(rName)
        , m_gender(gender)
        , m_age(age)
    {
    }

    QString m_name;
    EGender m_gender;
    int m_age;
    QList<CVideoFrame> m_facePictures;
};

class CFaceDataBase
{
public:
    static CFaceDataBase* GetSingleTon();
    int AddFace(const SFaceEntity& rEnt);   // return id
    void RemoveFace(int id);
    bool EditName(int id, const QString& rName);
    bool EditGender(int id, EGender gender);
    bool EditAge(int id, int age);
    bool EditVideoFrame(int id, const QList<CVideoFrame>& rFacePictures);

    bool GetFace(int id, SFaceEntity& rEnt) const;
    QStringList GetAllEntityName() const;

private:
    explicit CFaceDataBase();
    ~CFaceDataBase();
    static CFaceDataBase* sm_Instance;

    int m_maxID;
    QMap<int, SFaceEntity> m_mapIdtoFace;
};
#endif // FaceDataBase_h__
