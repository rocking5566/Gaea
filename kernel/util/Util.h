#ifndef Util_h__
#define Util_h__

#include <opencv2/core/core.hpp>
#include <QImage>
#include <QVector>
#include <QColor>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;
#define SAFE_DELETE_ARRAY(p) { if((p) != NULL) { delete[] (p);   (p)=NULL; } }

inline void MSleep (int milliseconds)
{
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif // win32
}

#endif // Util_h__
