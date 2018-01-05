#ifndef FLOAT4X4_H
#define FLOAT4X4_H

#include "float4.h"
#include "float3.h"

struct float4x4
{
	union
	{
		struct { float4 w, x, y, z; };
		float4 p[4];
	};
	
	float4x4() : w(0, 0, 0, 0), x(0, 0, 0, 0), y(0, 0, 0, 0), z(0, 0, 0, 0) {}

	float4x4(float4 _w, float4 _x, float4 _y, float4 _z) :
		w(_w), x(_x), y(_y), z(_z) {}

    //float** float4x4Matrix;

    //float4x4Matrix = new float* [4];
    
    //float4x4 float4x4Matrix = float4 f4[4];
    //float4 f4[4];

	float4 &operator[](int idx) { return p[idx]; }

	float4x4 multiplyBy(float4x4 &b);
	float4 multiplyBy(const float4 &b);

	friend std::ostream& operator<<(std::ostream& os, const float4x4& f4x4);

};

#endif // FLOAT4X4_H
