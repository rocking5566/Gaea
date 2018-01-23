#ifndef FaceDataBase_h__
#define FaceDataBase_h__
#include <QString>
#include <QList>
#include <QMap>
#include <QDate>
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
        , m_bankAreaCode(0)
    {}

    SMemberProperty(const QString& rIdentityCardId, const QString& rName, qulonglong bankAreaCode, const QDate& rBirthday, EGender gender)
        : m_identityCardId(rIdentityCardId)
        , m_name(rName)
        , m_bankAreaCode(bankAreaCode)
        , m_birthday(rBirthday)
        , m_gender(gender)
    {
    }

    QString m_identityCardId;
    QString m_name;
    qulonglong m_bankAreaCode;
    QDate m_birthday;
    EGender m_gender;
    QList<CImageAdaptor> m_facePictures;
};

class CMemberModel
{
public:
    static CMemberModel* GetSingleTon();
    int AddMember(const SMemberProperty& rMember);   // return member id
    void RemoveMember(int memberId);
    void Clear();
    bool EditIdentityCardId(int memberId, const QString& rIdentityCardId);
    bool EditName(int memberId, const QString& rName);
    bool EditBankAreaCode(int memberId, qulonglong bankAreaCode);
    bool EditBirthday(int memberId, const QDate& rBirthday);
    bool EditGender(int memberId, EGender gender);
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
