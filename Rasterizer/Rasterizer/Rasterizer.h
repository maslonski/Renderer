#include "float3.h"
#include "Buffer.h"


class Rasterizer {

public:

	typedef float3 float3;

	Buffer *colorBuffer;

	Rasterizer(Buffer *buffer) : colorBuffer(buffer) {};

	void drawTrinagle(const float3 &, const float3 &, const float3 &);
	void drawTrinagle(const float3 &, const float3 &, const float3 &, float3 &, float3 &, float3 &);

private:
	float min(float, float, float) noexcept;
	float max(float, float, float) noexcept;
	float min(float, float) noexcept;
	float max(float, float) noexcept;
};
