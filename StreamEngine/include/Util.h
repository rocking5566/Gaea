#ifndef Util_h__
#define Util_h__

#include <opencv2/core/core.hpp>
#include <QImage>
#include <QVector>
#include <QColor>
#ifdef WIN32
#define NOMINMAX    // Fix compile for std::min and std::max
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#if (defined WIN32 || defined _WIN32 || defined WINCE) && defined STREAM_ENGINE_API_EXPORT
#  define GAEA_EXPORTS __declspec(dllexport)
#else
#  define GAEA_EXPORTS
#endif
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
