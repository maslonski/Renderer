#ifndef FLOAT3_H
#define FLOAT3_H

#include <math.h>
#include <iostream>

#include "immintrin.h"
#include "xmmintrin.h"
#define _MM_SHUFFLE(a, b, c, d) ((a) << 6) | ((b) << 4) | ((c) << 2) | (d)

using std::cout;
using std::endl;

//spis metod gdzies zrobic moze

struct float3
{
	union {
		struct { float x, y, z; };
		struct { int r, g, b; };
		float p[3];
		__m128 mmv;
	};
	//chyba jeszcze konstruktory trzeba do r,g,b zrobic

	//------------------------------------------------------------------------------------------------
	//float3() : mmv(_mm_setzero_ps()) {}
	//float3(float x, float y, float z) : mmv(_mm_set_ps(0, z, y, x)) {}
	//------------------------------------------------------------------------------------------------

	float3() : x(0.f), y(0.f), z(0.f) {}

	float3(float _x, float _y, float _z = .0f) :
		x(_x), y(_y), z(_z) {}

	float &operator[](int idx) { return p[idx]; } // inaczej lekko niz na notatkach z szajerowych slajdow

	//friend float3 operator*(float f, const float3 &v); // in case of class

	//------------------------------------------------------------------------------------------------
	//operators overloading
	float3 operator+(const float3 &v) { return float3(x + v.x, y + v.y, z + v.z); }
	//float3 operator+(const float3 &v) { return _mm_add_ps(mmv, v.mmv); }

	float3 operator-(const float3 &v) { return float3(x - v.x, y - v.y, z - v.z); }
	//float3 operator-(const float3 &v) { return _mm_sub_ps(mmv, v.mmv); }

	//float3 operator*(const float3 &v) { return float3(x*v.x, y*v.y, z*v.z); }
	float3 operator*(const float3 &v) { return float3(x*v.x, y*v.y, z*v.z); }

	float3 operator/(const float3 &v) {
		if (v.x == 0 || v.y == 0 || v.z == 0)
		{
			cout << "Dzielnie przez zero!" << endl;
		} // mozna zoptymalizowac dzielenie, przyklad w doksie fgk
		else { return float3(x / v.x, y / v.y, z / v.z); }
	}

	//---
	float3 operator*(float f) { return float3(x*f, y*f, z*f); }
	//float3 operator*(float f) { return _mm_mul_ps(mmv, _mm_set1_ps(f)); }

	float3 operator/(float f) { return float3(x / f, y / f, z / f); }
	//---
	//------------------------------------------------------------------------------------------------

	//float3 operator*(float f, const float3 &v) { return float3(f*v.x, f*v.y, f*v.z); }

	float3 &operator-() { x = -x; y = -y; z = -z; return *this; } // wstepnie dziala

	//------------------------------------------------------------------------------------------------
	//float3 &operator +=(float3 v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
	float3 &operator +=(const float3 &v) { mmv = _mm_add_ps(mmv, v.mmv); return *this; }

	//float3 &operator -=(float3 v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
	float3 &operator -=(const float3 &v) { mmv = _mm_sub_ps(mmv, v.mmv); return *this; }

	//float3 &operator *=(float3 &v) { x*=v.x; y*=v.y; z*=v.z; return *this; }
	float3 &operator *=(const float3 &v) { mmv = _mm_mul_ps(mmv, v.mmv); return *this; }

	//float3 &operator /=(float3 &v) { x/=v.x; y/=v.y; z/=v.z; return *this; }
	float3 &operator /=(const float3 &v) { mmv = _mm_div_ps(mmv, v.mmv); return *this; }

	//------------------------------------------------------------------------------------------------

	bool operator ==(float3 v) { return (x == v.x && y == v.y && z == v.z); }
	bool operator !=(float3 v) { return (x != v.x || y != v.y || z != v.z); }

	//------------------------------------------------------------------------------------------------
	// Vector Products
	float scalarProduct(float3 v) { return (this->x * v.x + this->y + v.y + this->z + v.z); }
	/*float scalarProduct(const float3& b) const
	{
		return _mm_cvtss_f32(_mm_dp_ps(mmv, b.mmv, 0x71));
	}*/ // NIE DZIALA ZA BARDZO
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	//float3 crossProduct(float3 v) { return float3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }

	float3 crossProduct(const float3 &b) // CIEKAWE I TROCHE CHYBA COS NIE TAK // 57 SLAJD
	{
		float *mmTemp = new float[4];

		mmTemp = _mm_sub_ps(
			_mm_mul_ps(
				_mm_shuffle_ps(mmv, mmv, _MM_SHUFFLE(3, 0, 2, 1)),
				_mm_shuffle_ps(b.mmv, b.mmv, _MM_SHUFFLE(3, 1, 0, 2))),
			_mm_mul_ps(
				_mm_shuffle_ps(mmv, mmv, _MM_SHUFFLE(3, 1, 0, 2)),
				_mm_shuffle_ps(b.mmv, b.mmv, _MM_SHUFFLE(3, 0, 2, 1)))
		).m128_f32;
		return float3(mmTemp[1], mmTemp[2], mmTemp[3]);
	}
	//------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------
	float len() { return sqrt( (x*x)+(y*y)+(z*z) ) ; }
	//float len() { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(mmv, mmv, 0x71))); } // TEZ COS NIE ZA BARDZO
	//------------------------------------------------------------------------------------------------
    float sqrtLength() { return ( (x*x)+(y*y)+(z*z) ) ; }

    void normalize(); // bylo wczesniej float3
	//
	float3 normalizeWithReturn(); // bylo wczesniej float3
	//
    void magnitudeWTF(float);
    void negatefloat3(); //nie wiem czy potrzebne

    float3 reflect(float3, float3);
	///////////////////////////////////
	float saturate(float);
	float3 saturate(float3);
	/*float3 &operator <(float v) {
		if (x > 1.f || y > 1.f || z > 1.f) return float3(1.f, 1.f, 1.f);
		else if (x < 0.f || y < 0.f || z < 0.f) return float3(0.f, 0.f, 0.f);
	}*/
	//////////////////////////////////

    float3 toPoint(); // tez nie wiem czy dobrze
    float3 lerp(float3, float); // tez nie wiem czy dobrze2

    //access methods in case of class
    float getX() {return x;}
    float getY() {return y;}
    float getZ() {return z;}
    void setX (float _x) {this->x = _x;}
    void setY (float _y) {this->y = _y;}
    void setZ (float _z) {this->z = _z;}

    friend std::ostream& operator<<(std::ostream& os, const float3& f3);

};


//float3 operator*(float f, const float3 &v) { return float3(f*v.x, f*v.y, f*v.z); } // chwilowo wykomentowana

#endif // FLOAT3_H
