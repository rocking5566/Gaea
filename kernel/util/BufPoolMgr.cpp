#include "BufPoolMgr.h"
#include <stddef.h>

CBufPoolMgr* CBufPoolMgr::sm_Instance = NULL;

CBufPoolMgr* CBufPoolMgr::GetSingleTon()
{
    if (sm_Instance == NULL)
    {
        sm_Instance = new CBufPoolMgr();
    }

    return sm_Instance;
}

CBufPoolMgr::CBufPoolMgr()
{
    // TODO - define buffer pool size
}

CBufPoolMgr::~CBufPoolMgr()
{

}

char* CBufPoolMgr::Alloc(unsigned int size)
{
    return size > 0 ? new char[size] : NULL;
    // TODO - get memory from associate buffer pool
}

void CBufPoolMgr::Release(char* buf)
{
    delete[] buf;
    // TODO - send memory back to associate buffer pool
}

