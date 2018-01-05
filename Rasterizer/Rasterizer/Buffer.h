#pragma once

class Buffer
{
public:
	float *depth;
	unsigned int *color;
	int width, height, minX, maxX, minY, maxY, length;

	Buffer( int _width,   int _height) : width(_width), height(_height){
		color = new unsigned int[width * height];
		depth = new float[width * height];
	}

	/*Buffer(int _depth) : depth(_depth) {
		
	}*/

	void setSize();
	void clearColor(unsigned int);
	void clearDepth(float);

	//static int getWidth() { return width; }
	//static int getHeight() { return height; }

	virtual void save(char *) {};
};

