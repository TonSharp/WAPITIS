#pragma once

class Vec2
{
public:
	float X = 0, Y = 0;

	Vec2(float x, float y)
	{
		X = x;
		Y = y;
	}
};
class Vec3
{
public:
	float X = 0, Y = 0, Z = 0;

	Vec3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};
class Vec4
{
public:
	float X = 0, Y = 0, Z = 0, W = 0;

	Vec4(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
};

struct Vertex
{
	float X, Y, Z;
};

struct TextureCoord
{
	float X, Y;
};

struct Pixel3
{
	uint8_t R, G, B;
};
struct Pixel4
{
	uint8_t R, G, B, A;
};