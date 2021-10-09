#pragma once
#include <string>
#include <vector>

#include "Vertex.hpp"

using namespace std;

class Texture
{
private:

	uint8_t bitsPerPixel;
	uint16_t width, height;

	Pixel3* pixels3;
	Pixel4* pixels4;

	GLubyte* data;

	int dByteToInt(char* store)
	{
		return store[1] * 256 + store[0];
	}

	bool CheckHeader(FILE* file)
	{
		char* store = new char[2];

		fread(store, 1, 1, file);
		if (store[0] != 0)
			return false;

		fread(store, 1, 1, file);
		if (store[0] != 0)
			return false;

		fread(store, 1, 1, file);
		if (store[0] != 2)
			return false;

		fread(store, 1, 2, file);
		if (dByteToInt(store) != 0)
			return false;

		fread(store, 1, 2, file);
		if (dByteToInt(store) != 0)
			return false;

		fread(store, 1, 1, file);
		if (store[0] != 0)
			return false;

		fread(store, 1, 2, file);
		if (dByteToInt(store) != 0)
			return false;

		fread(store, 1, 2, file);
		if (dByteToInt(store) != 0)
			return false;

		fread(store, 1, 2, file);
		width = dByteToInt(store);

		fread(store, 1, 2, file);
		height = dByteToInt(store);

		fread(store, 1, 1, file);
		bitsPerPixel = store[0];

		fread(store, 1, 1, file);

		return true;
	}
	
public:

	GLuint ID;

	int GetBitsPerPixel()
	{
		return bitsPerPixel;
	}
	int GetWidth()
	{
		return width;
	}
	int GetHeight()
	{
		return height;
	}
	GLubyte* GetData()
	{
		return data;
	}
	Pixel3* Get3()
	{
		return pixels3;
	}
	Pixel4* Get4()
	{
		return pixels4;
	}

	void Load(string fname)
	{
		FILE* tga;
		fopen_s(&tga, fname.c_str(), "rb");

		if (!tga)
			return;

		if (!CheckHeader(tga))
			return;

		int inc = bitsPerPixel == 24 ? 3 : 4;

		uint8_t val;

		int ind = 0;
		int elemInd = 0;

		if (inc == 3)
			pixels3 = new Pixel3[width * height];
		else
			pixels4 = new Pixel4[width * height];

		data = new GLubyte[width * height * inc];


		for(int i = 0; i < inc * width * height; i += inc)
		{
			if(inc == 3)
			{
				fread(&val, 1, 1, tga);
				pixels3[ind].B = val;
				fread(&val, 1, 1, tga);
				pixels3[ind].G = val;
				fread(&val, 1, 1, tga);
				pixels3[ind].R = val;

				data[elemInd] = pixels3[ind].R;
				elemInd++;
				data[elemInd] = pixels3[ind].G;
				elemInd++;
				data[elemInd] = pixels3[ind].B;
				elemInd++;
			}
			else
			{
				fread(&val, 1, 1, tga);
				pixels4[ind].B = val;
				fread(&val, 1, 1, tga);
				pixels4[ind].G = val;
				fread(&val, 1, 1, tga);
				pixels4[ind].R = val;
				fread(&val, 1, 1, tga);
				pixels4[ind].A = val;

				data[elemInd] = pixels4[ind].R;
				elemInd++;
				data[elemInd] = pixels4[ind].G;
				elemInd++;
				data[elemInd] = pixels4[ind].B;
				elemInd++;
				data[elemInd] = pixels4[ind].A;
				elemInd++;
			}

			ind++;
		}
	}
};