#pragma once

#include <stdio.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "float3.h"
#include "Vertex.h"
#include "int3.h"
#include "Mesh.h"

using namespace std;

class OBJLoader : public Mesh{
protected:
	const string VERTICES_KEY = "v";
	const string FACES_KEY = "f";
	const string MAIN_SEPARATOR = " ";
	const string FACES_SEPARATOR_DOUBLE_SLASH = "//";
	const string FACES_SEPARATOR_SINGLE_SLASH = "/";

	vector<float3>* verticesList;
	vector<int3>* indicesList;

	float minVerticleValue, maxVerticleValue;

	void ParseLine(string &);
	void ParseVertices(vector<string> &);
	void ParseFaces(vector<string>&);
	void PrepareMesh();
	void CheckMinAndMaxVerticesValue(float3 &);
	float3 NormalizeVerices(float3);
	vector<string> Split(string& , string);

public:
	OBJLoader(string);
};