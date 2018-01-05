#pragma once

#include "float3.h"
#include "Vertex.h"
#include "VertexProcessor.h"

typedef Vertex Fragment;
class Light
{

public:

	float3 position;
	float3 ambient;/* = float3(.5f, .0f, .0f);*/
	float3 diffuse;
	float3 specular;
	float shininess;

	Light() : ambient(float3(.5f, .0f, .0f)), shininess(1.f) {}

	virtual float3 calculate(Fragment &, VertexProcessor &)=0;
};

