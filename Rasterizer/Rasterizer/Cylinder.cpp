#include "Cylinder.h"

Cylinder::Cylinder()
{
	vSize = vert * (horiz + 2);
	tSize = 2 * vert * horiz;
	vertices = new Vertex[vSize];
	indices = new int3[tSize];

	float y, r, x, z;

	for (int yy = 0; yy <= horiz + 1; ++yy)
	{
		y = cos(yy * PI / (horiz + 1.f)); // 1...-1
		r = 0.5f; //sqrt(1 - y*y); // = sin: 0...1..0
		for (int rr = 0; rr < vert; ++rr)
		{
			x = r*cos(2 * PI * rr / vert ); // wspolrzedne okregu
			z = r*sin(2 * PI * rr / vert ); // na plaszczyznie y
			vertices[rr + yy * vert].position = float3(x, y, z);
		}
	}

	for (int yy = 0; yy < horiz; ++yy)
		for (int rr = 0; rr < vert; ++rr)
		{
			indices[rr + 2 * yy*vert] = int3(
				(rr + 1) % vert + yy*vert,
				rr + vert + yy*vert,
				(rr + 1) % vert + vert + yy*vert
			);
			indices[rr + vert + 2 * yy*vert] = int3(
				rr + vert + yy*vert,
				rr + 2 * vert + yy*vert,
				(rr + 1) % vert + vert + yy*vert
			);
		}
}