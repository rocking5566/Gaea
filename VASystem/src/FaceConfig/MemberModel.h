#ifndef FaceDataBase_h__
#define FaceDataBase_h__
#include <QString>
#include <QList>
#include <QMap>
#include "ImageAdaptor.h"

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

struct SMemberProperty
{
    SMemberProperty()
        : m_gender(eMale)
        , m_age(0)
    {}

    SMemberProperty(const QString& rName, EGender gender, int age)
        : m_name(rName)
        , m_gender(gender)
        , m_age(age)
    {
    }

    QString m_name;
    EGender m_gender;
    int m_age;
    QList<CImageAdaptor> m_facePictures;
};

class CMemberModel
{
public:
    static CMemberModel* GetSingleTon();
    int AddMember(const SMemberProperty& rMember);   // return member id
    void RemoveMember(int memberId);
    bool EditName(int memberId, const QString& rName);
    bool EditGender(int memberId, EGender gender);
    bool EditAge(int memberId, int age);
    bool EditVideoFrame(int memberId, const QList<CImageAdaptor>& rFacePictures);

    bool GetMember(int memberId, SMemberProperty& rMember) const;

private:
    explicit CMemberModel();
    ~CMemberModel();
    static CMemberModel* sm_Instance;

    int m_maxMemberID;
    QMap<int, SMemberProperty> m_mapIdtoMember;
};
#endif // FaceDataBase_h__
