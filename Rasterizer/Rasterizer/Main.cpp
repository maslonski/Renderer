#include <iostream>

#include "Buffer.h"
#include "TgaBuffer.h"
//#include "Rasterizer.h"
#include "VertexProcessor.h"

#include "Mesh.h"
#include "SimpleTriangle.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cylinder.h"

//#include "DirectionalLight.h"
#include "PointLight.h"

#include "OBJLoader.h"

//#include <chrono>
#include <new>
#include <Windows.h>


using namespace std;
//------------------------------------------------------------------------------------------------------------
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}


//------------------------------------------------------------------------------------------------------------
int main() {
	

	//------------------------------------Mierzenie czasu - poczatek -----------------------------------------------
	float optimizationTime = .0f;
	//------------------------------------------------------------------------------------------------------------

	Buffer* colorBuffer = new (std::nothrow) TgaBuffer(512, 512);
	colorBuffer->clearColor(0xffffffff);
	colorBuffer->clearDepth(1000);

	Rasterizer rasterizer(colorBuffer);
	//----------------------------------------

	VertexProcessor vp;

	//ustawienie perspektywy
	vp.setPerspective(90.f, colorBuffer->length / colorBuffer->height, 10.0f, 1000.f);

	//float3 eye(10.0f, 10.0f, 10.0f);
	float3 eye(0.f, 0.f, 1.0f);
	float3 center(0.f, 0.f, 0.f);
	center.normalize();
	float3 up(0, 1, 0);

	vp.setLookat(eye, center, up);
	vp.setIdentity();
	//----------------------------------------

	Mesh m;
	SimpleTriangle st;
	Cube c;
	Sphere s;
	Cone cone;
	Cylinder cyl;

	OBJLoader *teapot = new OBJLoader("teapot.obj");
	//----------------Swiatla-----------------
	DirectionalLight dl;
	//dl.position = float3(.0f, .0f, .0f);

	PointLight pl;
	//pl.position = float3(0.0f, 0.0f, 0.0f);
	//----------------------------------------

	StartCounter();
	//----------Rysowanie obiektow------------

	vp.multByTranslation(float3(-0.5f, 0.5f, 0.f));
	vp.multByRotation(45, float3(0, 1, 0));
	vp.multByScale(float3(0.5f, 0.5f, 0.5f));
	teapot->draw(rasterizer, vp);
	vp.transform();
	vp.setIdentity();

	vp.multByTranslation(float3(0.0f, 0.0f, 0.f));
	vp.multByRotation(90, float3(0, 0, 1));
	vp.multByScale(float3(0.5f, 0.5f, 0.5f));
	teapot->draw(rasterizer, vp, pl);
	vp.transform();
	vp.setIdentity();
	//teapot->draw(rasterizer, vp, pl);
	//teapot->draw(rasterizer, vp, dl);

	//st.draw(rasterizer, vp);
	//st.draw(rasterizer, vp, dl);

	vp.multByTranslation(float3(0.8f, -0.8f, 0.f));
	vp.multByScale(float3(0.3f, 0.3f, 0.3f));
	c.draw(rasterizer, vp);
	vp.transform();
	vp.setIdentity();
	//c.draw(rasterizer, vp, dl);
	//c.draw(rasterizer, vp, pl);

	vp.multByTranslation(float3(-0.8f, -0.8f, 0.f));
	vp.multByScale(float3(0.3f, 0.3f, 0.3f));
	s.draw(rasterizer, vp);
	vp.transform();
	vp.setIdentity();
	//s.draw(rasterizer, vp, dl);
	//s.draw(rasterizer, vp, pl);


	vp.multByTranslation(float3(0.5f, 0.5f, 0.f));
	vp.multByScale(float3(0.3f, 0.3f, 0.3f));
	cone.draw(rasterizer, vp);
	vp.transform();
	vp.setIdentity();

	vp.multByTranslation(float3(0.f, 0.f, 0.f));
	vp.multByScale(float3(0.3f, 0.3f, 0.3f));
	s.draw(rasterizer, vp, pl);
	vp.transform();
	vp.setIdentity();


	vp.multByTranslation(float3(0.0f, -0.8f, 0.f));
	vp.multByScale(float3(0.3f, 0.3f, 0.3f));
	teapot->draw(rasterizer, vp, pl);
	vp.transform();
	vp.setIdentity();

	//cyl.draw(rasterizer, vp);
	//----------------------------------------
	//vp.transform();


	


	//------------------------------------------------------------------------------------------------------------

	//vp.multByTranslation(float3(-0.5f, -0.5f, 0.f)); //TRANSLATE
	//vp.multByScale(float3(0.5f, 0.5f, 0.5f)); //SCALE
	//vp.multByRotation(45, float3(0, 1, 0)); //ROTATE

	//--------------------------------------Przykladowy Trojkat---------------------------------------------------
	//vp.multByTranslation(float3(-0.5f, 0.f, 0.f));
	//vp.multByRotation(90, float3(0, 0, 1));
	//rasterizer.drawTrinagle( vp.tr(float3(-.5f, .0f, 0.0f)), vp.tr(float3(-.2f, .5f, 0.0f)), vp.tr(float3(.5f, .0f, 0.f)) );
	
	//vp.multByTranslation(float3(0.f, -0.5f, 0.f)); //TRANSLATE
	//vp.multByScale(float3(0.1f, 0.1f, 0.1f)); //SCALE
	//vp.multByRotation(45, float3(0, 1, 0)); //ROTATE

	//vp.transform();
	//------------------------------------------------------------------------------------------------------------
	//-----------------------------Dwa stare przecinajace sie trojkaty--------------------------------------------
	//rasterizer.drawTrinagle(float3(-.5f, .0f, .0f), float3(-.2f, .5f, .0f), float3(.5f, .0f, 0.f));

	//rasterizer.drawTrinagle(float3(-.5f, -.5f, 1.f), float3(.0f, .3f, -.1f), float3(.5f, -.5f, 1.f));
	//------------------------------------------------------------------------------------------------------------

	
	//-------------------------------------Mierzenie czasu - koniec ------------------------------------------------
	//cout << GetCounter() << "\n";
	optimizationTime = GetCounter();
	//--------------------------------------------------------------------------------------------------------------

	ofstream myfile;
	myfile.open("optimizationTimes.txt", ios::app);
	myfile << optimizationTime << "ms\n";
	myfile.close();

	//system("pause");
	colorBuffer->save("Test.tga");
	

}



















/*
high_resolution_clock::time_point t1 = high_resolution_clock::now();
high_resolution_clock::time_point t2 = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(t2 - t1).count();
cout << duration << "ms" << endl;
*/


/*
//------------------------------------------------------------------------
//const clock_t begin_time = clock();

//std::chrono::time_point<std::chrono::system_clock> start, end;
//start = std::chrono::system_clock::now();
//end = std::chrono::system_clock::now();

//auto start_time = std::chrono::high_resolution_clock::now();


//high_resolution_clock::time_point t1 = high_resolution_clock::now();
//------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------
//----------------------------------------Mierzenie czasu 1---------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
//system("pause");

//std::chrono::duration<double> elapsed_seconds = end - start;
//std::time_t end_time = std::chrono::system_clock::to_time_t(end);

//std::cout << "finished computation at " << std::ctime(&end_time)
//<< "elapsed time: " << elapsed_seconds.count() << "s\n";
//------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//----------------------------------------Mierzenie czasu 2---------------------------------------------------
//------------------------------------------------------------------------------------------------------------
//auto end_time = std::chrono::high_resolution_clock::now();
//auto time = end_time - start_time;

//std::cout << "Renderer " <<
//std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << " to run.\n";


//high_resolution_clock::time_point t2 = high_resolution_clock::now();

//auto duration = duration_cast<milliseconds>(t2 - t1).count();

//cout << duration << "ms" << endl;
//------------------------------------------------------------------------------------------------------------
*/






/*
//Zwykly trojkat
//rasterizer.drawTrinagle(float3(50.f, 50.f), float3(200.f, 100.f), float3(150.f, 50.f));

//Sprawdzenie Culling-u:
//rasterizer.drawTrinagle(float3(150.f, 200.f), float3(200.f, 300.f), float3(50.f, 200.f));

//Sprawdzenie przycinania figury:
//rasterizer.drawTrinagle(float3(250.f, 50.f), float3(400.f, 100.f), float3(600.f, 50.f));

//Dodatkowy odwrocony trojkat
//rasterizer.drawTrinagle(float3(50.f, 200.f), float3(150.f, 200.f), float3(100.f, 100.f));

//Poprzez zakres [-1,1]
//rasterizer.drawTrinagle(float3(-0.2f, -0.8f), float3(0.5f, -0.5f), float3(0.8f, -0.8f));
//rasterizer.drawTrinagle(float3(0.2f, 0.2f), float3(0.5f, 0.5f), float3(0.4f, 0.2f));

//rasterizer.drawTrinagle(float3(-0.5f, 0.f), float3(0.6f, 0.5f), float3(0.8f, -0.2f));

//ladna interpolacja kolorow, ale szary jeden, bo slaby jakis
//rasterizer.drawTrinagle(float3(-0.5f, .0f), float3(.0f, 0.5f), float3(0.5f, .0f));

//rasterizer.drawTrinagle(float3(-1.f, .0f, 0.f), float3(.0f, 1.f, 0.f), float3(1.f, .0f, 0.f));*/