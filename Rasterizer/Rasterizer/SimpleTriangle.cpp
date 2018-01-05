#include "SimpleTriangle.h"

SimpleTriangle::SimpleTriangle()
{
	vSize = 3;
	tSize = 1;
	vertices = new Vertex[vSize];
	indices = new int3[tSize];

	vertices[0].position = float3(-.5f, 0.f, 0.f);
	vertices[1].position = float3(0.f, .5f, 0.f);
	vertices[2].position = float3(.5f, 0.f, 0.f);

	indices[0] = int3(0, 1, 2);
}