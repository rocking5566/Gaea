#ifndef BufMgr_h__
#define BufMgr_h__

typedef unsigned char uchar;

class CBufPoolMgr
{
public:
    static CBufPoolMgr* GetSingleTon();

    uchar* Alloc(unsigned int size);
    void Release(uchar* buf);

private:
    CBufPoolMgr();
    ~CBufPoolMgr();

private:
    static CBufPoolMgr* sm_Instance;

};
#endif // BufMgr_h__