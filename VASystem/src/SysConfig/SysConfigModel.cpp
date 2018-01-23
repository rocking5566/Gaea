#include "SysConfigModel.h"

CSysConfigModel* CSysConfigModel::sm_Instance = NULL;

CSysConfigModel* CSysConfigModel::GetSingleTon()
{
    if (sm_Instance == NULL)
    {
        sm_Instance = new CSysConfigModel();
    }

    return sm_Instance;
}

void CSysConfigModel::Clear()
{
    // [TODO] update config file
    m_sysBankAreaCode = 0;
}

void CSysConfigModel::SetBankAreaCode(qulonglong sysBankAreaCode)
{
    // [TODO] update config file
    m_sysBankAreaCode = sysBankAreaCode;
}

qulonglong CSysConfigModel::GetBankAreaCode()
{
    return m_sysBankAreaCode;
}

CSysConfigModel::CSysConfigModel()
    : m_sysBankAreaCode(0)
{

}

CSysConfigModel::~CSysConfigModel()
{

}
