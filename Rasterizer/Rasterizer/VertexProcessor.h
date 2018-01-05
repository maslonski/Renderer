#pragma once

#include <math.h>
#include "float3.h"
#include "float4x4.h"
#include "float4.h"

#define PI 3.14159265358979323846

class VertexProcessor
{
public:
	VertexProcessor() {};

	float4x4 obj2world;
	float4x4 view2proj;// = float4x4();
	float4x4 world2view;// = float4x4();
	float4x4 obj2proj;
	//
	float4x4 obj2view;
	//


	void transform();
	void setIdentity();
	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookat(float3 eye, float3 center, float3 up);

	void multByTranslation(float3 &v);
	void multByScale(float3 &v);
	void multByRotation(float a, float3 &v);

	float3 tr(const float3 &);
};

