#include <iostream>
#include "Rasterizer.h"
#include "Buffer.h"

/*void Rasterizer::drawTrinagle(const float3 &v1, const float3 &v2, const float3 &v3) {
	float y1 = v1.y;
	float y2 = v2.y;
	float y3 = v3.y;

	float x1 = v1.x;
	float x2 = v2.x;
	float x3 = v3.x;

	int minX = (int)min(x1, x2, x3);
	int minY = (int)min(y1, y2, y3);
	int maxX = (int)max(x1, x2, x3);
	int maxY = (int)max(y1, y2, y3);

	/*Sprawdzenie czy rysowana figura nie znajduje sie poza buforem*/
/*	minX = max(minX, 0);
	maxX = min(maxX, colorBuffer->width - 1);
	minY = max(minY, 0);
	maxY = min(maxY, colorBuffer->height - 1);


	int stride = minY * colorBuffer->height;

	for (int y = minY; y < maxY; y++) {
		for (int x = minX; x < maxX; x++) {
			if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) >= 0 &&
				(x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) >= 0 &&
				(x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) >= 0) {
				colorBuffer->color[x + stride] = 0xffff0000;
			}
		}
		stride += colorBuffer->height;
	}
}*/

void Rasterizer::drawTrinagle(const float3 &v1, const float3 &v2, const float3 &v3) {

	int x1 = (v1.x + 1) * colorBuffer->width * .5f;
	int x2 = (v2.x + 1) * colorBuffer->width * .5f;
	int x3 = (v3.x + 1) * colorBuffer->width * .5f;

	int y1 = (v1.y + 1) * colorBuffer->height * .5f;
	int y2 = (v2.y + 1) * colorBuffer->height * .5f;
	int y3 = (v3.y + 1) * colorBuffer->height * .5f;
	//----------------------------------------------

	/*cout << "v1= " << v1 << endl;
	cout << "v2= " << v2 << endl;
	cout << "v3= " << v3 << endl;
	system("pause");*/

	//-----------------------------------------------
	//int z1 = (v1.z + 1) * colorBuffer->depth * .5f;
	//int z2 = (v2.z + 1) * colorBuffer->depth * .5f;
	//int z3 = (v3.z + 1) * colorBuffer->depth * .5f;

	float3 *c1 = new float3(255, 0, 0);
	float3 *c2 = new float3(0, 255, 0);
	float3 *c3 = new float3(0, 0, 255);

	// Krawedzie top-left
	bool tl1, tl2, tl3;
	tl1 = tl2 = tl3 = false;


	/*float y1 = v1.y;
	float y2 = v2.y;
	float y3 = v3.y;

	float x1 = v1.x;
	float x2 = v2.x;
	float x3 = v3.x;*/


	//Obcinanie
	int minX = (int)min(x1, x2, x3) + .5f;
	int maxX = (int)max(x1, x2, x3) + .5f;

	int minY = (int)min(y1, y2, y3) + .5f;
	int maxY = (int)max(y1, y2, y3) + .5f;

	/*Sprawdzenie czy rysowana figura nie znajduje sie poza buforem*/
	minX = max(minX, 0);
	maxX = min(maxX, colorBuffer->width - 1);
	minY = max(minY, 0);
	maxY = min(maxY, colorBuffer->height - 1);

	float dx12 = x1 - x2;
	float dx23 = x2 - x3;
	float dx31 = x3 - x1;
	float dy12 = y1 - y2;
	float dy23 = y2 - y3;
	float dy31 = y3 - y1;

	// Wykrywanie krawedzi top-left
	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) { tl1 = true; }
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) { tl2 = true; }
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) { tl3 = true; }

	//float lambda1, lambda2, lambda3;
	//lambda1 = lambda2 = lambda3 = 0;

	int step = minY * colorBuffer->height;
	
	for (int y = minY; y <= maxY; y++) {// minY 50 ; maxY 100
		for (int x = minX; x <= maxX; x++) {// minX 50 ; maxX 200

			/*if ((dx12) * (y - y1) - (dy12) * (x - x1) > 0 &&
				(dx23) * (y - y2) - (dy23) * (x - x2) > 0 &&
				(dx31) * (y - y3) - (dy31) * (x - x3) > 0) {*/

			
			if(
				(tl1 == true ? ( (dx12) * (y - y1) - (dy12) * (x - x1) > 0 ) : ( (dx12) * (y - y1) - (dy12) * (x - x1) >= 0 ))

				&&

				(tl2 == true ? ( (dx23) * (y - y2) - (dy23) * (x - x2) > 0 ) : ( (dx23) * (y - y2) - (dy23) * (x - x2) >= 0 ))

				&&

				(tl3 == true ? ( (dx31) * (y - y3) - (dy31) * (x - x3) > 0 ): ( (dx31) * (y - y3) - (dy31) * (x - x3) >= 0 ))
				
			){

				//Wspolrzedne barycentryczne // lambda1 + lambda2 + lambda3 = 1

				float lambda1 = (float)((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3))
					/ (float)((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));

				float lambda2 = (float)((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3))
					/ (float)((y3 - y1)*(x2 - x3) + (x1 - x3)*(y2 - y3));

				float lambda3 = 1.0f - lambda1 - lambda2;

				// Obliczanie koloru przy uzyciu wspolrzednych barycentrycznych
				// do optymalizacji ten kod troszeczke
				float colorR = (lambda1 * c1->x + lambda2 * c2->x + lambda3 * c3->x);
				float colorG = (lambda1 * c1->y + lambda2 * c2->y + lambda3 * c3->y);
				float colorB = (lambda1 * c1->z + lambda2 * c2->z + lambda3 * c3->z);
				//float colorR = floatColorR/* * 255*/;
				//float colorG = floatColorG/* * 255*/;
				//float colorB = floatColorB/* * 255*/;

				//colorBuffer->color[x + step] = ((255 & 0xFF) << 24) | (((int)(lambda1*x1 + lambda1*y1) & 0xff) << 16) | (((int)(lambda2*x2 + lambda2*y2) & 0xff) << 8) | (((int)(lambda3*x3 + lambda3*y3) & 0xff) << 0);

				float depth = (lambda1 * v1.z + lambda2 * v2.z + lambda3 * v3.z);
				//std::cout << "depth: " << depth << std::endl;
				//std::cout << "colorBuffer->depth[x]: " << colorBuffer->depth[x] << std::endl;
				if (depth < colorBuffer->depth[x + step]) {
					colorBuffer->color[x + step] = ((255 & 0xFF) << 24) | (((int)colorR & 0xFF) << 16) | (((int)colorG & 0xFF) << 8) | (((int)colorB & 0xFF) << 0);
					colorBuffer->depth[x + step] = depth; 
				}
			}
		}//koniec wewnetrzenego fora
		step += colorBuffer->height;
	}
}

void Rasterizer::drawTrinagle(const float3 &v1, const float3 &v2, const float3 &v3, float3 &l1, float3 &l2, float3 &l3)
{
	int x1 = (v1.x + 1) * colorBuffer->width * .5f;
	int x2 = (v2.x + 1) * colorBuffer->width * .5f;
	int x3 = (v3.x + 1) * colorBuffer->width * .5f;

	int y1 = (v1.y + 1) * colorBuffer->height * .5f;
	int y2 = (v2.y + 1) * colorBuffer->height * .5f;
	int y3 = (v3.y + 1) * colorBuffer->height * .5f;
	//----------------------------------------------

	/*cout << "v1= " << v1 << endl;
	cout << "v2= " << v2 << endl;
	cout << "v3= " << v3 << endl;
	system("pause");*/

	//-----------------------------------------------
	//int z1 = (v1.z + 1) * colorBuffer->depth * .5f;
	//int z2 = (v2.z + 1) * colorBuffer->depth * .5f;
	//int z3 = (v3.z + 1) * colorBuffer->depth * .5f;

	float3 *c1 = &l1;
	float3 *c2 = &l2;
	float3 *c3 = &l3;

	// Krawedzie top-left
	bool tl1, tl2, tl3;
	tl1 = tl2 = tl3 = false;


	/*float y1 = v1.y;
	float y2 = v2.y;
	float y3 = v3.y;

	float x1 = v1.x;
	float x2 = v2.x;
	float x3 = v3.x;*/


	//Obcinanie
	int minX = (int)(min(x1, x2, x3) + .5f);
	int maxX = (int)(max(x1, x2, x3) + .5f);

	int minY = (int)(min(y1, y2, y3) + .5f);
	int maxY = (int)(max(y1, y2, y3) + .5f);

	/*Sprawdzenie czy rysowana figura nie znajduje sie poza buforem*/
	minX = max(minX, 0);
	maxX = min(maxX, colorBuffer->width - 1);
	minY = max(minY, 0);
	maxY = min(maxY, colorBuffer->height - 1);

	float dx12 = x1 - x2;
	float dx23 = x2 - x3;
	float dx31 = x3 - x1;
	float dy12 = y1 - y2;
	float dy23 = y2 - y3;
	float dy31 = y3 - y1;

	// Wykrywanie krawedzi top-left
	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) { tl1 = true; }
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) { tl2 = true; }
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) { tl3 = true; }

	//float lambda1, lambda2, lambda3;
	//lambda1 = lambda2 = lambda3 = 0;

	int step = minY * colorBuffer->height;

	for (int y = minY; y <= maxY; ++y) {// minY 50 ; maxY 100
		for (int x = minX; x <= maxX; ++x) {// minX 50 ; maxX 200

										   /*if ((dx12) * (y - y1) - (dy12) * (x - x1) > 0 &&
										   (dx23) * (y - y2) - (dy23) * (x - x2) > 0 &&
										   (dx31) * (y - y3) - (dy31) * (x - x3) > 0) {*/


			if (
				(tl1 == true ? ((dx12) * (y - y1) - (dy12) * (x - x1) > 0) : ((dx12) * (y - y1) - (dy12) * (x - x1) >= 0))

				&&

				(tl2 == true ? ((dx23) * (y - y2) - (dy23) * (x - x2) > 0) : ((dx23) * (y - y2) - (dy23) * (x - x2) >= 0))

				&&

				(tl3 == true ? ((dx31) * (y - y3) - (dy31) * (x - x3) > 0) : ((dx31) * (y - y3) - (dy31) * (x - x3) >= 0))

				) {

				//Wspolrzedne barycentryczne // lambda1 + lambda2 + lambda3 = 1

				float lambda1 = (float)((y2 - y3)*(x - x3) + (x3 - x2)*(y - y3))
					/ (float)((y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3));

				float lambda2 = (float)((y3 - y1)*(x - x3) + (x1 - x3)*(y - y3))
					/ (float)((y3 - y1)*(x2 - x3) + (x1 - x3)*(y2 - y3));

				float lambda3 = 1.0f - lambda1 - lambda2;

				// Obliczanie koloru przy uzyciu wspolrzednych barycentrycznych
				// do optymalizacji ten kod troszeczke
				
				float colorR = (lambda1 * c1->x + lambda2 * c2->x + lambda3 * c3->x);
				float colorG = (lambda1 * c1->y + lambda2 * c2->y + lambda3 * c3->y);
				float colorB = (lambda1 * c1->z + lambda2 * c2->z + lambda3 * c3->z);

				// Test w ramach swiatel
				/*float colorR = (lambda1 * c1->x + lambda2 * c1->y + lambda3 * c1->z);
				float colorG = (lambda1 * c2->x + lambda2 * c2->y + lambda3 * c2->z);
				float colorB = (lambda1 * c3->x + lambda2 * c3->y + lambda3 * c3->z);*/

				//float colorR = floatColorR/* * 255*/;
				//float colorG = floatColorG/* * 255*/;
				//float colorB = floatColorB/* * 255*/;

				//colorBuffer->color[x + step] = ((255 & 0xFF) << 24) | (((int)(lambda1*x1 + lambda1*y1) & 0xff) << 16) | (((int)(lambda2*x2 + lambda2*y2) & 0xff) << 8) | (((int)(lambda3*x3 + lambda3*y3) & 0xff) << 0);

				float depth = (lambda1 * v1.z + lambda2 * v2.z + lambda3 * v3.z);
				//std::cout << "depth: " << depth << std::endl;
				//std::cout << "colorBuffer->depth[x]: " << colorBuffer->depth[x] << std::endl;
				if (depth < colorBuffer->depth[x + step]) {
					colorBuffer->color[x + step] = ((255 & 0xFF) << 24) | (((int)colorR & 0xFF) << 16) | (((int)colorG & 0xFF) << 8) | (((int)colorB & 0xFF) << 0);
					colorBuffer->depth[x + step] = depth;
				}
			}
		}//koniec wewnetrzenego fora
		step += colorBuffer->height;
	}

}

float Rasterizer::min(float x1, float x2, float x3) noexcept{
	float min = x1;

	if (x2 < min)
		min = x2;
	if (x3 < min)
		min = x3;

	return min;
}

float Rasterizer::min(float x1, float x2) noexcept {
	float min = x1;

	if (x2 < min)
		min = x2;

	return min;
}

float Rasterizer::max(float x1, float x2, float x3) noexcept {
	float max = x1;

	if (x2 > max)
		max = x2;
	if (x3 > max)
		max = x3;

	return max;
}

float Rasterizer::max(float x1, float x2) noexcept{
	float max = x1;

	if (x2 > max)
		max = x2;

	return max;
}
