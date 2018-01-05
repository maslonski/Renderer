#pragma once
#include "Vertex.h"
#include "int3.h"
#include "Rasterizer.h"
#include "VertexProcessor.h"

#include "DirectionalLight.h"

class Mesh
{

public:

	int vSize, tSize;
	Vertex *vertices;
	int3  *indices;


//public:

	Mesh();

	void draw(Rasterizer &, VertexProcessor &);
	void draw(Rasterizer &, VertexProcessor &, Light &);

	void makeNormals();
};

