#include "Cube.h"

Cube::Cube()
{
	vSize = 8;
	tSize = 12;
	vertices = new Vertex[vSize];
	indices = new int3[tSize];

	vertices[0].position = float3(-.5f, .5f, -.5f);
	vertices[1].position = float3(-.5f, .5f, .0f);

	vertices[2].position = float3(-.5f, -.5f, -.5f);
	vertices[3].position = float3(-.5f, -.5f, .0f);

	vertices[4].position = float3(.5f, .5f, -.5f);
	vertices[5].position = float3(.5f, .5f, 0.f);

	vertices[6].position = float3(.5f, -.5f, -.5f);
	vertices[7].position = float3(.5f, -.5f, 0.f);


	indices[0] = int3(1, 5, 3);
	indices[1] = int3(3, 5, 7);

	indices[2] = int3(0, 4, 1);
	indices[3] = int3(1, 4, 5);

	indices[4] = int3(0, 1, 3);
	indices[5] = int3(2, 0, 3);

	indices[6] = int3(0, 4, 2);
	indices[7] = int3(2, 4, 6);

	indices[8] = int3(6, 4, 7);
	indices[9] = int3(4, 5, 7);

	indices[10] = int3(2, 6, 7);
	indices[11] = int3(2, 7, 3);








	/*vertices[8].setPosition(float3(.5f, 0.f, 0.f));

	vertices[9].setPosition(float3(.5f, 0.f, 0.f));
	vertices[10].setPosition(float3(.5f, 0.f, 0.f));
	vertices[11].setPosition(float3(.5f, 0.f, 0.f));

	vertices[12].setPosition(float3(.5f, 0.f, 0.f));
	vertices[13].setPosition(float3(.5f, 0.f, 0.f));
	vertices[14].setPosition(float3(.5f, 0.f, 0.f));

	vertices[15].setPosition(float3(.5f, 0.f, 0.f));
	vertices[16].setPosition(float3(.5f, 0.f, 0.f));
	vertices[17].setPosition(float3(.5f, 0.f, 0.f));

	vertices[18].setPosition(float3(.5f, 0.f, 0.f));
	vertices[19].setPosition(float3(.5f, 0.f, 0.f));
	vertices[20].setPosition(float3(.5f, 0.f, 0.f));

	vertices[21].setPosition(float3(.5f, 0.f, 0.f));
	vertices[22].setPosition(float3(.5f, 0.f, 0.f));
	vertices[23].setPosition(float3(.5f, 0.f, 0.f));

	vertices[24].setPosition(float3(.5f, 0.f, 0.f));
	vertices[25].setPosition(float3(.5f, 0.f, 0.f));
	vertices[26].setPosition(float3(.5f, 0.f, 0.f));

	vertices[27].setPosition(float3(.5f, 0.f, 0.f));
	vertices[28].setPosition(float3(.5f, 0.f, 0.f));
	vertices[29].setPosition(float3(.5f, 0.f, 0.f));

	vertices[30].setPosition(float3(.5f, 0.f, 0.f));
	vertices[31].setPosition(float3(.5f, 0.f, 0.f));
	vertices[32].setPosition(float3(.5f, 0.f, 0.f));

	vertices[33].setPosition(float3(.5f, 0.f, 0.f));
	vertices[34].setPosition(float3(.5f, 0.f, 0.f));
	vertices[35].setPosition(float3(.5f, 0.f, 0.f));*/





}