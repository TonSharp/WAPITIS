#pragma once
#include "Vertex.hpp"

struct Material
{
	Vertex Ambient;
	Vertex Diffuse;
	Vertex Specular;
	float Shiness;
};