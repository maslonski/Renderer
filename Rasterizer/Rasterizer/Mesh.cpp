#include "Mesh.h"

Mesh::Mesh()
{
}

void Mesh::draw(Rasterizer &r, VertexProcessor &vp)
{
	
	for (int i = 0; i < this->tSize; ++i) {
		r.drawTrinagle(
			vp.tr(vertices[indices[i].x].position),
			vp.tr(vertices[indices[i].y].position),
			vp.tr(vertices[indices[i].z].position)
		);
		//std::cout << "vertices[i]" << vertices[indices[i].x].position << std::endl;
		
	}
	makeNormals(); // POKI CO WYKOMENTOWANE
}

void Mesh::draw(Rasterizer &r, VertexProcessor &vp, Light &l)
{
	
	float3 lPosition = l.position;
	l.position = l.position.reflect(l.position, l.position);

	
	for (int i = 0; i < this->tSize; ++i) {
		
		Vertex v1;
		v1.setVertex(vertices[indices[i].x].position, vertices[indices[i].x].normal);
		Vertex v2;
		v2.setVertex(vertices[indices[i].x].position, vertices[indices[i].x].normal);
		Vertex v3;
		v3.setVertex(vertices[indices[i].x].position, vertices[indices[i].x].normal);

		r.drawTrinagle(
			vp.tr(vertices[indices[i].x].position),
			vp.tr(vertices[indices[i].y].position),
			vp.tr(vertices[indices[i].z].position),
			l.calculate(v1, vp),
			l.calculate(v2, vp),
			l.calculate(v3, vp)
			
		);
		//std::cout << "vertices[i]" << vertices[indices[i].x].position << std::endl;
	}
	makeNormals(); // POKI CO WYKOMENTOWANE
}

void Mesh::makeNormals()
{
	float3 nTemp1, nTemp2, n;
	for (int i = 0; i < vSize; ++i)
		vertices[i].normal = float3(0.f, 0.f, 0.f);
	for (int i = 0; i < tSize; ++i)
	{
		nTemp1 = (vertices[indices[i].z].position
			- vertices[indices[i].x].position);
		nTemp2 = (vertices[indices[i].y].position
			- vertices[indices[i].x].position);

		n = nTemp1.crossProduct(nTemp2);
		n.normalize();

		vertices[indices[i].x].normal += n;
		vertices[indices[i].y].normal += n;
		vertices[indices[i].z].normal += n;
	}
	for (int i = 0; i < vSize; ++i)
		vertices[i].normal.normalize();
}
