#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	DirectionalLight();

	float3 calculate(Fragment &, VertexProcessor &);
};

