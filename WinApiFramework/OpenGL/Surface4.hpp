#pragma once
#include <vector>
#include "GLContext.hpp"

using namespace std;

struct Surface4
{
	Vertex normal;
	Vertex points[4];
	TextureCoord texCoords[4];
};