#pragma once


#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "Glu32.lib")

#include "GLContext.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "GameObject.hpp"

#define GL_WINDOW WS_POPUP | WS_CLIPCHILDREN |WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW