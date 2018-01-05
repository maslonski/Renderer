#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
}

float3 DirectionalLight::calculate(Fragment &f, VertexProcessor &vp) {
	
	float3 N = vp.tr(f.normal);
	float3 V = vp.tr(-f.position);
	float3 R = f.position.reflect(position, N);

	//--------------------------------------------------------
	/*float4 tmp1 = vp.obj2view.multiplyBy(float4(f.normal.x, f.normal.y, f.normal.z, 1));
	float3 N = float3(tmp1.x, tmp1.y, tmp1.z);
	float4 tmp2 = vp.obj2view.multiplyBy(float4(-f.position.x, -f.position.y, -f.position.z, 1));
	float3 V = float3(tmp2.x, tmp2.y, tmp2.z);
	float3 R = f.position.reflect(position, N);*/
	//--------------------------------------------------------


	float floatDiffuse = position.saturate(position.scalarProduct(N));
	float floatSpecular = pow(R.scalarProduct(V), shininess);

	diffuse.x = diffuse.y = diffuse.z = floatDiffuse;
	specular.x = specular.y = specular.z = floatSpecular;
	
	return ((ambient + diffuse + specular).saturate(ambient + diffuse + specular)) * 255;
	//return float3(1.f, 0.f, 0.f);

	//return ambient + diffuse + specular;

	/*N = normalize(vp.tr.obj2view(f.normal))
	V = vp normalize(vp.tr.obj2view(-f.position));
	R = normalize(reflect(L, N));
	dif = saturate(dot(L, N));
	spec = pow(saturate(dot(R, V)), 100));*/


	//return float3(0.f, 0.f, 0.f);
}