#include "db-util.hpp"

Vec3 normalize(const Vec3 &v)
{
	float l = length(v);
	if (l != 0.0f)
	{
		return v / l;
	}
	else
	{
		return Vec3(1, 0, 0);
	}
}

Vec2 normalize(const Vec2 &v)
{
	float l = length(v);
	if (l != 0.0f)
	{
		return v / l;
	}
	else
	{
		return Vec2(1, 0);
	}
}

Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
	Vec3 res;
	return *D3DXVec3Cross(&res, &v1, &v2);
}

float frand()
{
	return rand() / (float)RAND_MAX;
}

float frand(float min, float max)
{
	return frand() * (max - min) + min;
}

float expFalloff(float current, float target, float rate, float dt)
{
	return target + (current - target) * powf(2.0f, -dt * rate);
}



////////////////////////////////////////////////////////////////////
// Oscillator style functions
////////////////////////////////////////////////////////////////////

float periodicSin(float time, float period, float min, float max)
{
	float t = sinf((time / (2.0f * M_PI)) / period);
	return (t + 1.0f) / 2.0f * (max - min) + min;
}

float periodicCos(float time, float period, float min, float max)
{
	float t = cosf((time / (2.0f * M_PI)) / period);
	return (t + 1.0f) / 2.0f * (max - min) + min;
}

float periodicTriangle(float time, float period, float min, float max)
{
	float t = time / period + 0.5f;
	t = abs((t - floorf(t)) -0.5f) * 2.0f;
	return t * (max - min) + min;
}

float periodicRamp(float time, float period, float min, float max)
{
	float t = time / period;
	t = t - floorf(t);
	return t * (max - min) + min;
}

float step(float time, float startTime, float endTime, float startValue, float endValue)
{
	float t = saturate((time - startTime) / (endTime - startTime));
	return t * (endValue - startValue) + startValue;
}

float smoothStep(float time, float startTime, float endTime, float startValue, float endValue)
{
	float t = saturate((time - startTime) / (endTime - startTime));
	t = t * t * (3 - t * t);
	return t * (endValue - startValue) + startValue;
}