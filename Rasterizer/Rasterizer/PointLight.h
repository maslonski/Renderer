#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight();

	float3 calculate(Fragment &, VertexProcessor &);
};

