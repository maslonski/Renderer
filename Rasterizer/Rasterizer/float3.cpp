#include "float3.h"

float const epsilon = 0.0001f;

void float3::normalize() {
        float length = this->len();
        if (length > epsilon) {
            x /= length; y/= length; z /= length;
        }
		else x=y=z=0.0f;

//        if(fabs(x)<.001f && fabs(y)<.001f && fabs(z)<.001f)
//            return float3(0.f, 0.f, 0.f);
//        else
//            return *this/sqrt(x*x+y*y);
}

float3 float3::normalizeWithReturn()
{
	float length = this->len();
	if (length > epsilon) {
		return float3(x /= length, y /= length, z /= length);
	}
	else return float3(.0f, .0f, .0f);

	//        if(fabs(x)<.001f && fabs(y)<.001f && fabs(z)<.001f)
	//            return float3(0.f, 0.f, 0.f);
	//        else
	//            return *this/sqrt(x*x+y*y);
}

void float3::magnitudeWTF(float f) {
    this->x *= f;// moze bez thisow ?
    this->y *= f;
    this->z *= f;
}

void float3::negatefloat3() {
    this->x = -this->x;// moze bez thisow ?
    this->y = -this->y;
    this->z = -this->z;
}

float3 float3::reflect(float3 v, float3 n)
{
	return v - n * (v.scalarProduct(n)) * 2;
}

float float3::saturate(float f)
{
	if (f<0) return 0.f;
	else if (f>1.f) return 1.f;
}

float3 float3::saturate(float3 f)
{
	return float3(saturate(f.x), saturate(f.y), saturate(f.z));
}

/*float3 float3::reflect(float3 v) { // trzeba sprawdzic czy dobrze
    return *this - (2 * this->scalarProduct(v) * v);
}*/

// tez nie wiem czy dobrze
float3 float3::toPoint() {
    float3 *p = new float3(this->x, this->y, this->z);
    return *p;
}

float3 float3::lerp(float3 v, float t) {
    float3 *vec = new float3();
    vec->x = this->x + t * (v.x - this->x);
    return *vec;
}

std::ostream & operator<<(std::ostream & os, const float3 & f3)
{
	return os << "[" << f3.x << ", " << f3.y << ", " << f3.z << "]" << std::endl;
}
