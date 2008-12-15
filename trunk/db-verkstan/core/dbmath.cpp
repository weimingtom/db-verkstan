extern "C"
{
    float __cdecl sin(float v)
    {
        __asm fld v;
        __asm fsin;
        __asm fstp v;
        return v;
    }

    float __cdecl cos(float v)
    {
        __asm fld v;
        __asm fcos;
        __asm fstp v;
        return v;
    }

	void __cdecl sincos(float v, float &outSin, float &outCos)
    {
        __asm fld v;
        __asm fsincos;
        __asm fstp outSin;
		__asm fstp outCos;
    }

    float __cdecl sqrt(float v)
    {
        __asm fld v;
        __asm fsqrt;
        __asm fstp v;
        return v;
    }

    float __cdecl pow(float x, float y)
    {
        return x;
    }

    float __cdecl log(float v)
    {
        __asm fld1;
        __asm fld v;
        __asm fyl2x;
        __asm fstp v;
        return v;
    }

    int __cdecl _ftol2(float f)
    {
        volatile int result;
        __asm fistp result;
        return result;
    }

    int __cdecl _ftol2_sse(float f)
    {
        volatile int result;
        __asm fistp result;
        return result;
    }

    float __cdecl fmod(float x, float y)
    {
        return 0.0f;
    }

    float __cdecl tanh(float v)
    {
        return v;
    }

    float __cdecl fabs(float v)
    {
        float register result = v;
        __asm fld result;
        __asm fstp result;
        return result;
    }
}