#pragma once

#include <gl/GL.h>
#include <gl/GLU.h>
#include <Windows.h>

#include "../Elements/Window.hpp"

struct GLColor
{
	BYTE R, G, B, A;
};

struct RGBAColor
{
	UINT8 R, G, B, A;
};

GLColor RGBToGL(RGBAColor color)
{
	GLColor cl = { 0 };

	cl.R = (float)color.R / 255;
	cl.G = (float)color.G / 255;
	cl.B = (float)color.B / 255;
	cl.A = (float)color.A / 255;

	return cl;
}
RGBAColor GLToRGB(GLColor color)
{
	RGBAColor cl = { 0 };

	cl.R = (float)color.R * 255;
	cl.G = (float)color.G * 255;
	cl.B = (float)color.B * 255;
	cl.A = (float)color.A * 255;

	return cl;
}

class GLContext
{
private:

	HDC hDC;
	HGLRC hRC;

	Window* parent;

	void (*sceneRenderer)();

public:

	GLContext(Window* wnd, DWORD flags, BYTE colorBits, BYTE depthBits, void (*renderer)())
	{
		hDC = GetDC(wnd->Get());

		parent = wnd;

		PIXELFORMATDESCRIPTOR pd;
		memset(&pd, 0, sizeof(PIXELFORMATDESCRIPTOR));

		pd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pd.nVersion = 1;
		pd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | flags;
		pd.iPixelType = PFD_TYPE_RGBA;
		pd.cColorBits = colorBits;
		pd.cDepthBits = depthBits;

		int iPixelFormat = ChoosePixelFormat(hDC, &pd);

		PIXELFORMATDESCRIPTOR bestMatch_pd;
		DescribePixelFormat(hDC, iPixelFormat, sizeof(pd), &bestMatch_pd);

		SetPixelFormat(hDC, iPixelFormat, &pd);

		hRC = wglCreateContext(hDC);
		wglMakeCurrent(hDC, hRC);

		sceneRenderer = renderer;
	}

	void Init()
	{
		RECT rect;
		GetClientRect(*parent, &rect);

		ClearColor(0, 0, 0, 255);
		
		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);

		glShadeModel(GL_SMOOTH);        // разрешить плавное цветовое сглаживание
		glMatrixMode(GL_PROJECTION);    // Выбор матрицы проекции
		glLoadIdentity();               // Сброс матрицы проекции
		gluPerspective(45.0f, (GLfloat)rect.right / (GLfloat)rect.bottom, 0.1f, 100.0f);

		// Вычислить соотношение геометрических размеров для окна
		glMatrixMode(GL_MODELVIEW);     // Выбор матрицы просмотра модели

		Render();
	}

	void ResizeScene(float width, float height)
	{
		if (height == 0)
			height = 1;

		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);

		Render();
	}

	void ClearColor(UINT8 r, UINT8 g, UINT8 b, UINT8 a)
	{
		glClearColor((float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255);
		InvalidateRect(*parent, NULL, true);
	}

	void ClearBuffers(DWORD buffers)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | buffers);
		glLoadIdentity();
	}

	void Render()
	{
		if (this == nullptr)
			return;

		//parent->StartDraw();

		if (sceneRenderer != nullptr)
			sceneRenderer();

		//parent->StopDraw();
	}

	void Destroy()
	{
		if (hRC != NULL)
		{
			wglMakeCurrent(NULL, NULL); 
			wglDeleteContext(hRC);
			hRC = NULL;
		}

		if (hDC != NULL)
		{
			ReleaseDC(*parent, hDC);
			hDC = NULL;
		}
	}

	HDC HDC()
	{
		return hDC;
	}
};