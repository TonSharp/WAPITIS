#pragma once


#include "Libs/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "OpenGL/Libs/GL/glew32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "Glu32.lib")
//#pragma comment(lib, "../OpenGL/Libs/GL/glew32s.lib")

#include "GLContext.hpp"
#include "Model.hpp"
#include "GameObject.hpp"

#include "Libs/glm/glm.hpp"
#include "Libs/glm/gtc/matrix_transform.hpp"
#include "Libs/glm/gtc/type_ptr.hpp"



#define GL_WINDOW WS_POPUP | WS_CLIPCHILDREN |WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW