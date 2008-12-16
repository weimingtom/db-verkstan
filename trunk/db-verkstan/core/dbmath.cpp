/*
extern "C"
{
    float __cdecl sinf(float v)
    {
        _asm fld dword ptr [v]
        _asm fsin;
        _asm fstp dword ptr [v]

        return v;
    }

    float __cdecl sin(float v)
    {
        _asm fld dword ptr [v]
        _asm fsin;
        _asm fstp dword ptr [v]

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
        __asm fld v;
        __asm fabs;
        __asm fstp v;
        return v;
    }
}
*/