#include "core/externals.hpp"

typedef unsigned char byte;

extern "C" int _fltused = 1;

void *__cdecl memcpy(void *pvDest, const void *pvSrc, size_t count)
{
    byte    *begin  =   (byte*)pvDest;
    byte    *src    =   (byte*)pvSrc;
    byte    *end    =   begin + count;

    for(; begin != end; ++begin, ++src)
    {
        *begin = *src;
    }

    return pvDest;
}

extern "C"
{
    void* memset(void *ptr, int val, size_t size)
    {
        char* Rover = (char*)ptr;
        while(size-- > 0)
           *Rover++ = (char)val;
        return ptr;
    }
}

void* operator new(size_t sz) 
{
    return HeapAlloc(GetProcessHeap(), 0, sz);
}

void operator delete(void* m) 
{
    HeapFree(GetProcessHeap(), 0, m);
}

/**
 * Exists to get rid of a link error when compiling with no default libs.
 * When calling a pure virtual function from a constructor or destructor,
 * CLR shows a warning message, and as CLR is not present, well we simply
 * add an empty implementation of the function.
 */
extern "C" int _cdecl _purecall()
{
   return 0;
}