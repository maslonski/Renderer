#include "float4.h"

float float4::dotProduct(const float4 &anotherVector) const {
	return x * anotherVector.x + y * anotherVector.y + z * anotherVector.z + w * anotherVector.w;
}

std::ostream & operator<<(std::ostream & os, const float4 & f4)
{
	return os << "[" << f4.x << ", " << f4.y << ", " << f4.z << ", " << f4.w <<"]" << std::endl;
}
