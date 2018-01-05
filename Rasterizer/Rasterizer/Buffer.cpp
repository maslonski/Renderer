#include "Buffer.h"

void Buffer::setSize() {

}

void Buffer::clearColor(unsigned int color) {
	for (int i = 0; i < width*height; i++) {
		this->color[i] = color;
	}
}

void Buffer::clearDepth(float depth) {
	for (int i = 0; i < width*height; i++) {
		this->depth[i] = depth;
	}
}
