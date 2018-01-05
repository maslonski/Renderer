#include "VertexProcessor.h"

void VertexProcessor::setIdentity() {
	obj2world = float4x4(
		float4(1.0f, 0.0f, 0.0f, 0.0f),
		float4(0.0f, 1.0f, 0.0f, 0.0f),
		float4(0.0f, 0.0f, 1.0f, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
	);
}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far) {
	fovy *= PI / 360;
	float f = cos(fovy) / sin(fovy);
	//view2proj[0] = float4(f / aspect, 0, 0, 0);
	view2proj.p[0] = float4(f / aspect, 0, 0, 0);
	view2proj.p[1] = float4(0, f, 0, 0);
	view2proj.p[2] = float4(0, 0, (far + near) / (near - far), -1);
	view2proj.p[3] = float4(0, 0, 2 * far * near / (near - far), 0 );
}

void VertexProcessor::setLookat(float3 eye, float3 center, float3 up)
{
	float3 f = center - eye;
	f.normalize();
	up.normalize();
	float3 s = f.crossProduct(up);
	float3 u = s.crossProduct(f);
	world2view[0] = float4(s[0], u[0], -f[0], 0);
	world2view[1] = float4(s[1], u[1], -f[1], 0);
	world2view[2] = float4(s[2], u[2], -f[2], 0);
	//world2view[3] = float4(-eye, 1);
	world2view[3] = float4(0, 0, 0, 1.f);
}

void VertexProcessor::transform() {

	//std::cout << "obj2world "<< obj2world << std::endl;
	obj2view = world2view.multiplyBy(obj2world);
	//std::cout << "obj2view "<< obj2view << std::endl;

	//obj2proj = view2proj.multiplyBy(obj2view); // ZMIANA
	obj2world = view2proj.multiplyBy(obj2view); // ZMIANA

	//std::cout << "obj2proj: " << obj2proj << std::endl;
	//system("pause");

	//obj2proj = obj2world.multiplyBy(world2view);
	//obj2proj = obj2proj.multiplyBy(view2proj);
}

float3 VertexProcessor::tr(const float3 & v) { //in object space

	float4 *f4Temp = new float4(v.x, v.y, v.z, 1.0f);
	//float4 r = obj2proj.multiplyBy(*f4Temp); // ZMIANA
	float4 r = obj2world.multiplyBy(*f4Temp); // ZMIANA
	//std::cout << "obj2proj: " << obj2proj << std::endl;

	//float4 r = obj2proj.multiplyBy(float4(v.x, v.y, v.z, 1.0f/*v.w*/));

	//std::cout << obj2proj << std::endl;
	//---
	//std::cout <<  r.x << std::endl;
	//std::cout << r.y  << std::endl;
	//std::cout << r.z << std::endl;
	//std::cout << r << std::endl;


	//float3 *f3 = new float3(r.x / r.w, r.y / r.w, r.z / r.w);
	//std::cout <<  float3(r.x / r.w, r.y / r.w, r.z / r.w) << std::endl;
	//---

	//system("pause");
	return float3(r.x, r.y, r.z); //we get vector in unified cube from -1,-1,-1 to 1,1,1 // ZMIANA
	//return float3(r.x / r.w, r.y / r.w, r.z / r.w); //we get vector in unified cube from -1,-1,-1 to 1,1,1
}

void VertexProcessor::multByTranslation(float3 &v)
{
	/*float4x4 m(
		float4(1, 0, 0, 0),
		float4(0, 1, 0, 0),
		float4(0, 0, 1, 0),
		float4(v.x, v.y, v.z, 1) );
	obj2world = m.multiplyBy(obj2world);*/

	float4x4 m(
		float4(1.0, 0.0f, 0.0f, v.x),
		float4(0.0, 1.0f, 0.0f, v.y),
		float4(0.0, 0.0f, 1.0f, v.z),
		float4(0, 0, 0, 1.0f) );

	//float4x4 m = float4x4(row1, row2, row3, row4); wykomentowane na d³u¿ej

	obj2world = m.multiplyBy(obj2world);

}

void VertexProcessor::multByScale(float3 &v)
{
	float4x4 m(
		float4(v.x, 0, 0, 0),
		float4(0, v.y, 0, 0),
		float4(0, 0, v.z, 0),
		float4(0, 0, 0,	  1) );
	obj2world = m.multiplyBy(obj2world);
}

void VertexProcessor::multByRotation(float a, float3 &v)
{
	float s = sin(a*PI / 180), c = cos(a*PI / 180);
	v.normalize();
	float4x4 m(
		float4(v.x * v.x * (1 - c) + c, v.y * v.x * (1 - c) + v.z * s,
			v.x * v.z * (1 - c) - v.y * s, 0),
		float4(v.x * v.y * (1 - c) - v.z * s, v.y * v.y * (1 - c) + c,
			v.y * v.z * (1 - c) - v.x * s, 0),
		float4(v.x * v.z * (1 - c) + v.y * s, v.y * v.z * (1 - c) - v.x*s,
			v.z * v.z * (1 - c) + c, 0),
		float4(0, 0, 0, 1) );
	obj2world = m.multiplyBy(obj2world);

	/*float4 row1 = float4(v.x*v.x*(1 - c) + c, v.y*v.x*(1 - c) + v.z*s, v.x*v.z*(1 - c) - v.y*s, 0.0f);
	float4 row2 = float4(v.x*v.y*(1 - c) - v.z*s, v.y*v.y*(1 - c) + c, v.y*v.z*(1 - c) + v.x*s, 0.0f);
	float4 row3 = float4(v.x*v.z*(1 - c) + v.y*s, v.y*v.z*(1 - c) - v.x*s, v.z*v.z*(1 - c) + c, 0.0f);
	float4 row4 = float4(0.0, 0.0f, 0.0f, 1.0f);


	float4x4 m = float4x4(row1, row2, row3, row4);

	//obj2world = m.multiplyBy(obj2world);*/
}
