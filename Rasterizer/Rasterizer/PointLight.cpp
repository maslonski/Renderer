#include "PointLight.h"

PointLight::PointLight()
{
}

float3 PointLight::calculate(Fragment &f, VertexProcessor &vp) {

	float3 N = vp.tr(f.normal);
	float3 V = vp.tr(-f.position);
	float3 L = (position - V).normalizeWithReturn();
	V.normalize();
	float3 R = R.reflect(L, N);

	//--------------------------------------------------------
	/*float3 temp;

	float4 tmp1 = vp.obj2view.multiplyBy(float4(f.normal.x, f.normal.y, f.normal.z, 1));
	float3 N = float3(tmp1.x, tmp1.y, tmp1.z);
	N.normalize();

	float3 minusPosition = float3(0.f, 0.f, 0.f) - f.position;

	float4 tmp2 = vp.obj2view.multiplyBy(float4(-f.position.x, -f.position.y, -f.position.z, 1));
	float3 V = float3(tmp2.x, tmp2.y, tmp2.z);
	float3 L = position - V;
	//L.normalize();
	//V.normalize();

	float3 reflected = L.reflect(L, N);
	float3 R = reflected;*/
	//R.normalize();
	//--------------------------------------------------------
	/*float dotted1 = temp.scalarProduct(N);
	float diff = temp.saturate(dotted1);
	float dotted2 = temp.scalarProduct(V);
	
	float spec = pow(dotted2, 50);
	float3 newdiff = diffuse * diff;
	float3 newspec = specular * spec;
	float3 col = ambient + newdiff;
	col = col + newspec;
	float3 newcol = col.saturate(col);
	return newcol;*/

	/*float3 L = (position - V).normalizeWithReturn();

	L.normalize();
	V.normalize();
	float3 R = f.position.reflect(L, N);*/
	//--------------------------------------------------------

	

	float floatDiffuse = position.saturate(L.scalarProduct(N));
	float floatSpecular = pow(R.scalarProduct(V), shininess);

	diffuse.x = diffuse.y = diffuse.z = floatDiffuse;
	specular.x = specular.y = specular.z = floatSpecular;

	return ((ambient + diffuse + specular).saturate(ambient + diffuse + specular)) * 255 ;
	

	
	
	/*float3 temp;

	float4 tmp1 = vp.obj2view.mulByfloat4(vp.obj2view, float4(v.normal.x, v.normal.y, v.normal.z, 1));



	float3	N = float3(tmp1.x1, tmp1.x2, tmp1.x3);
	N.normalize(N);


	float3 minusPosition = temp.diff(float3(0, 0, 0), v.position);



	float4 tmp = vp.obj2view.mulByfloat4(vp.obj2view, float4(minusPosition.x, minusPosition.y, minusPosition.z, 1));
	float3 	V = float3(tmp.x1, tmp.x2, tmp.x3);


	float3 L = temp.diff(position, V);
	L = L.normalize(L);
	V = V.normalize(V);

	float3 reflected = L.reflect(L, N);
	float3 R = reflected;
	R = R.normalize(R);


	float dotted1 = temp.dot(L, N);
	float diff = temp.saturateScalar(dotted1);
	float dotted2 = temp.dot(R, V);
	//float saturated = temp.saturateScalar(dotted2);
	float spec = pow(dotted2, 50);
	float3 newdiff = L.mul(diffuse, diff);
	float3 newspec = L.mul(specular, spec);
	float3 col = newdiff.add(ambient, newdiff);
	col = col.add(col, newspec);
	float3 newcol = col.saturateF3(col);
	return newcol;*/

	return float3(0.f, 0.f, 0.f);
}