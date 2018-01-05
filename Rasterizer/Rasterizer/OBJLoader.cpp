#include "OBJLoader.h"


OBJLoader::OBJLoader(string inputFileName) : verticesList(new vector<float3>()), 
	indicesList(new vector<int3>()), 
	minVerticleValue(0), 
	maxVerticleValue(0)
{
	ifstream file(inputFileName);
	string line;

	while (getline(file, line))
	{
		ParseLine(line);
	}

	PrepareMesh();
}

void OBJLoader::ParseLine(string &line)
{
	vector<string> splitedLine = Split(line, MAIN_SEPARATOR);

	if (splitedLine.size() > 0)
	{
		string lineKey = splitedLine[0];

		if (lineKey == VERTICES_KEY) {
			ParseVertices(splitedLine);
			return;
		}

		if (lineKey == FACES_KEY) {
			ParseFaces(splitedLine);
			return;
		}
	}
}

vector<string> OBJLoader::Split(string &word, string separator)
{
	char* cStr = const_cast<char*>(word.c_str());
	char* currentChar;
	vector<string> result;
	currentChar = strtok(cStr, separator.c_str());
	while (currentChar != NULL) {
		result.push_back(currentChar);
		currentChar = strtok(NULL, separator.c_str());
	}
	return result;
}

void OBJLoader::ParseVertices(vector<string> &splitedLine)
{	
	float x = atof(splitedLine[1].c_str());
	float y = atof(splitedLine[2].c_str());
	float z = atof(splitedLine[3].c_str());

	float3 apex = float3(x, y, z);
	CheckMinAndMaxVerticesValue(apex);

	verticesList->push_back(apex);
}

void OBJLoader::ParseFaces(vector<string> &splitedLine)
{
	string faceSeparator;

	if (splitedLine[1].find(FACES_SEPARATOR_DOUBLE_SLASH) != string::npos) {
		string faceSeparator = FACES_SEPARATOR_DOUBLE_SLASH;
	}
	else if (splitedLine[1].find(FACES_SEPARATOR_SINGLE_SLASH) != string::npos) {
		string faceSeparator = FACES_SEPARATOR_SINGLE_SLASH;
	}
	else {
		int faceA = atoi(splitedLine[1].c_str()) - 1;
		int faceB = atoi(splitedLine[2].c_str()) - 1;
		int faceC = atoi(splitedLine[3].c_str()) - 1;

		indicesList->push_back(int3(faceA, faceB, faceC));

		return;
	}

	vector<string> separateFacesIndices = Split(splitedLine[1], faceSeparator);
	
	int faceA = atoi(separateFacesIndices[0].c_str()) - 1;
	int faceB = atoi(separateFacesIndices[1].c_str()) - 1;
	int faceC = atoi(separateFacesIndices[2].c_str()) - 1;

	indicesList->push_back(int3(faceA, faceB, faceC));
}

void OBJLoader::PrepareMesh()
{
	vSize = verticesList->size();
	tSize = indicesList->size();

	vertices = new Vertex[vSize];
	indices = new int3[tSize];

	for (int i = 0; i < vSize; i++)
	{
		vertices[i].position = NormalizeVerices(verticesList->at(i));
	}

	for (int i = 0; i < tSize; i++)
	{
		indices[i] = indicesList->at(i);
	}
}

void OBJLoader::CheckMinAndMaxVerticesValue(float3 &value)
{
	if (value.x < minVerticleValue) {
		minVerticleValue = value.x;
	}

	if (value.y < minVerticleValue) {
		minVerticleValue = value.y;
	}

	if (value.z < minVerticleValue) {
		minVerticleValue = value.z;
	}

	if (value.x > maxVerticleValue) {
		maxVerticleValue = value.x;
	}

	if (value.y > maxVerticleValue) {
		maxVerticleValue = value.y;
	}

	if (value.z > maxVerticleValue) {
		maxVerticleValue = value.z;
	}
}

float3 OBJLoader::NormalizeVerices(float3 value)
{
	float numeratorSection = (maxVerticleValue + minVerticleValue) / 2;
	float denominatorSection = (maxVerticleValue - minVerticleValue) / 2;

	float normalizedX = (value.x - numeratorSection) / denominatorSection;
	float normalizedY = (value.y - numeratorSection) / denominatorSection;
	float normalizedZ = (value.z - numeratorSection) / denominatorSection;
	
	return float3(normalizedX, normalizedY, normalizedZ);
}
