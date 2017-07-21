#ifndef BufMgr_h__
#define BufMgr_h__

class CBufPoolMgr
{
public:
    static CBufPoolMgr* GetSingleTon();

    char* Alloc(unsigned int size);
    void Release(char* buf);

private:
    CBufPoolMgr();
    ~CBufPoolMgr();

private:
    static CBufPoolMgr* sm_Instance;

};
#endif // BufMgr_h__