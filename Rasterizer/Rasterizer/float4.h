#ifndef FLOAT4_H
#define FLOAT4_H

#include "float3.h"

struct float4
{
    union {
        struct {float x, y, z, w;};
        struct {int r, g, b, a;};
		float p[4];
    };

    //float4(): x(0), y(0), z(0), w(0) {}

	float4(float _x, float _y, float _z, float _w=1.f) :
		x(_x), y(_y), z(_z), w(_w) {}

	float4(float3 _f3, float _f):
		x(_f3.x), y(_f3.y), z(_f3.z), w(_f) {}

    float &operator[](int idx) { return p[idx]; } // inaczej lekko niz na notatkach z szajerowych slajdow


	float dotProduct(const float4 &anotherVector) const;

	//float4 operator*(float4 v) { return float4(x*v.x, y*v.y, z*v.z, w*v.w); }

	friend std::ostream& operator<<(std::ostream& os, const float4& f4);
};

#endif // FLOAT4_H
