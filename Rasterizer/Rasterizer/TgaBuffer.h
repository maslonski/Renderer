#pragma once

#include <string>
#include <stdio.h>

#include "Buffer.h"

class TgaBuffer : public Buffer
{
public:
	unsigned short header[9] = {
		0x0000, 0x0002, 0x0000, 0x000, 0x0000, 0x0000,
		0x0100, 0x0100, //width, height
		0x0820 };

	TgaBuffer(int width, int height) : Buffer(width, height) {};

	void save(char *);
};

