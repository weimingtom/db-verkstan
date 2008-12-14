extern "C"
{
    float sin(float v)
    {
        __asm fld v;
        __asm fsin;
        __asm fstp v;
        return v;
    }

    float cos(float v)
    {
        __asm fld v;
        __asm fcos;
        __asm fstp v;
        return v;
    }

    float sqrt(float x)
    {
        return x;
    }

    float pow(float x, float y)
    {
        return x;
    }

    float powf(float x, float y)
    {
        return x;
    }

    float log(float x)
    {
        return x;
    }

    int _ftol2(float f)
    {
        volatile int result;
        __asm fistp result;
        return result;
    }

    int _ftol2_sse(float f)
    {
        volatile int result;
        __asm fistp result;
        return result;
    }

    float fmodf(float x, float y)
    {
        return 0.0f;
    }

    float tanhf(float v)
    {
        return v;
    }

    float fabsf(float v)
    {
        return v;
    }

    float fabs(float v)
    {
        return v;
    }

    float __max(float v1, float v2)
    {
        return 0.0f;
    }

    float abs(float v)
    {
        return v;
    }
}