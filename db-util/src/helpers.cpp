#include "db-util.hpp"

Vec3 normalize(const Vec3 &v)
{
	return v / length(v);
}

Vec2 normalize(const Vec2 &v)
{
	return v / length(v);
}

float dot(const Vec3 &v1, const Vec3 &v2)
{
	return D3DXVec3Dot(&v1, &v2);
}

float dot(const Vec2 &v1, const Vec2 &v2)
{
	return D3DXVec2Dot(&v1, &v2);
}

Vec3 cross(const Vec3 &v1, const Vec3 &v2)
{
	Vec3 res;
	return *D3DXVec3Cross(&res, &v1, &v2);
}

float length(const Vec3 &v)
{
	return D3DXVec3Length(&v);
}

float length(const Vec2 &v)
{
	return D3DXVec2Length(&v);
}

float lengthSq(const Vec3 &v)
{
	return D3DXVec3LengthSq(&v);
}

float lengthSq(const Vec2 &v)
{
	return D3DXVec2LengthSq(&v);
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