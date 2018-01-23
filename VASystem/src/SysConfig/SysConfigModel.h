#ifndef SysConfigModel_h__
#define SysConfigModel_h__

#include <QString>

class CSysConfigModel
{
public:
    static CSysConfigModel* GetSingleTon();
    void SetBankAreaCode(qulonglong sysBankAreaCode);
    qulonglong GetBankAreaCode();

private:
    explicit CSysConfigModel();
    ~CSysConfigModel();
    static CSysConfigModel* sm_Instance;

    qulonglong m_sysBankAreaCode;
};
#endif // SysConfigModel_h__