#include "TgaBuffer.h"

void TgaBuffer::save(char *fileName) {
	FILE *f = fopen(fileName, "wb+");
	//if (NULL == f) return -1;

	header[6] = width;
	header[7] = height;

	fwrite(header, 2, 9, f);
	fwrite(color, 4, width*height, f);

	fclose(f);
}
