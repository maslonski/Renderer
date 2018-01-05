#include "float4x4.h"

float4x4 float4x4::multiplyBy(float4x4 &b) {
	float4x4 c = float4x4();

	c.p[0] = float4(
		p[0].x * b.p[0].x + p[1].x * b.p[0].y + p[2].x * b.p[0].z + p[3].x * b.p[0].w,
		p[0].y * b.p[0].x + p[1].y * b.p[0].y + p[2].y * b.p[0].z + p[3].y * b.p[0].w,
		p[0].z * b.p[0].x + p[1].z * b.p[0].y + p[2].z * b.p[0].z + p[3].z * b.p[0].w,
		p[0].w * b.p[0].x + p[1].w * b.p[0].y + p[2].w * b.p[0].z + p[3].w * b.p[0].w
	);

	c.p[1] = float4(
		p[0].x * b.p[1].x + p[1].x * b.p[1].y + p[2].x * b.p[1].z + p[3].x * b.p[1].w,
		p[0].y * b.p[1].x + p[1].y * b.p[1].y + p[2].y * b.p[1].z + p[3].y * b.p[1].w,
		p[0].z * b.p[1].x + p[1].z * b.p[1].y + p[2].z * b.p[1].z + p[3].z * b.p[1].w,
		p[0].w * b.p[1].x + p[1].w * b.p[1].y + p[2].w * b.p[1].z + p[3].w * b.p[1].w
	);

	c.p[2] = float4(
		p[0].x * b.p[2].x + p[1].x * b.p[2].y + p[2].x * b.p[2].z + p[3].x * b.p[2].w,
		p[0].y * b.p[2].x + p[1].y * b.p[2].y + p[2].y * b.p[2].z + p[3].y * b.p[2].w,
		p[0].z * b.p[2].x + p[1].z * b.p[2].y + p[2].z * b.p[2].z + p[3].z * b.p[2].w,
		p[0].w * b.p[2].x + p[1].w * b.p[2].y + p[2].w * b.p[2].z + p[3].w * b.p[2].w
	);

	c.p[3] = float4(
		p[0].x * b.p[3].x + p[1].x * b.p[3].y + p[2].x * b.p[3].z + p[3].x * b.p[3].w,
		p[0].y * b.p[3].x + p[1].y * b.p[3].y + p[2].y * b.p[3].z + p[3].y * b.p[3].w,
		p[0].z * b.p[3].x + p[1].z * b.p[3].y + p[2].z * b.p[3].z + p[3].z * b.p[3].w,
		p[0].w * b.p[3].x + p[1].w * b.p[3].y + p[2].w * b.p[3].z + p[3].w * b.p[3].w
	);
	return c;

}

float4 float4x4::multiplyBy(const float4 &b) {
	//based on http://stackoverflow.com/questions/25805126/vector-matrix-product-efficiency-issue
	float4x4 a = *this; //getTransposed(); ???

	float4 result(
		a[0].dotProduct(b),
		a[1].dotProduct(b),
		a[2].dotProduct(b),
		a[3].dotProduct(b)
	);
	//std::cout << "result: " << b << std::endl;
	return result;
}

std::ostream & operator<<(std::ostream & os, const float4x4 & f4x4)
{
	return os <<std::endl<< "|" << f4x4.w << ", " << f4x4.x << ", " << f4x4.y << ", " << f4x4.z << "|" << std::endl;
}
