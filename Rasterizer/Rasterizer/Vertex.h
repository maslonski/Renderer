#pragma once
#include "float3.h"

class Vertex
{
	
public:

	float3 position, normal;

	//float3 getPostion() { return this->position; }
	//float3 getNormal() { return this->normal; }

	//void setPosition(float3 pos) { this->position = pos; }
	//void setNormal(float3 norm) { this->normal = norm; }

	void setVertex(float3 &, float3 &);

};

