#pragma once

////////////////////////////////////////////////////////////////////
// Vector helpers
////////////////////////////////////////////////////////////////////

typedef D3DXVECTOR3 Vec3;
typedef D3DXVECTOR2 Vec2;

Vec3 normalize(const Vec3 &v);

Vec2 normalize(const Vec2 &v);

float dot(const Vec3 &v1, const Vec3 &v2);

float dot(const Vec2 &v1, const Vec2 &v2);

Vec3 cross(const Vec3 &v1, const Vec3 &v2);

float length(const Vec3 &v);

float length(const Vec2 &v);

float lengthSq(const Vec3 &v);

float lengthSq(const Vec2 &v);

////////////////////////////////////////////////////////////////////
// Random numbers, wraps rand so you can reset seed with srand
////////////////////////////////////////////////////////////////////

// Returns random float in [0, 1]
float frand();

// Returns random float in [min, max]
float frand(float min, float max);


////////////////////////////////////////////////////////////////////
// Number crunching helpers
////////////////////////////////////////////////////////////////////

float clamp(float a, float min, float max);

inline float saturate(float a) { return clamp(a, 0.0f, 1.0f); }