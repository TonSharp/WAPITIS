#pragma once
#include <Windows.h>
#include <vector>

#include "../Framework/Elements/Window.hpp"
#include "Libs/OpenGL.hpp"
#include "GLLibs.hpp"
#include "Vertex.hpp"

struct GLColor
{
	float R, G, B, A;
};

struct RGBAColor
{
	float R, G, B, A;
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

void DrawPolygon(vector<Vertex> vertexes, RGBAColor color)
{
	GLColor clr = RGBToGL(color);
	glColor3f(clr.R, clr.G, clr.B);

	glBegin(GL_POLYGON);

	for (auto &vert : vertexes)
		glVertex3f(vert.X, vert.Y, vert.Z);

	glEnd();
}

void DrawTriangles(vector<Vertex> vertexes, RGBAColor color)
{
	GLColor clr = RGBToGL(color);
	glColor3f(clr.R, clr.G, clr.B);

	glBegin(GL_POLYGON);

	for (auto& vert : vertexes)
		glVertex3f(vert.X, vert.Y, vert.Z);

	glEnd();
}

void DrawQuads(vector<Vertex> vertexes, RGBAColor color)
{
	GLColor clr = RGBToGL(color);
	glColor3f(clr.R, clr.G, clr.B);

	glBegin(GL_QUADS);

	for (auto& vert : vertexes)
		glVertex3f(vert.X, vert.Y, vert.Z);

	glEnd();
}
void DrawQuads(vector<Vertex> vertexes, RGBAColor color, Vertex normal)
{
	GLColor clr = RGBToGL(color);
	glColor3f(clr.R, clr.G, clr.B);

	glBegin(GL_QUADS);

	glNormal3f(normal.X, normal.Y, normal.Z);

	for (auto& vert : vertexes)
		glVertex3f(vert.X, vert.Y, vert.Z);

	glEnd();
}

void DrawBox(Vertex center, float width, float height, float depth, RGBAColor color)
{
	//Bottom
	DrawQuads(
		{
			{center.X - width / 2, center.Y - height / 2, center.Z - depth / 2},
			{center.X - width / 2, center.Y - height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y - height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y - height / 2, center.Z - depth / 2}
		},
		color,
		{0, -1, 0}
	);

	//Top
	DrawQuads(
		{
			{center.X - width / 2, center.Y + height / 2, center.Z - depth / 2},
			{center.X - width / 2, center.Y + height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y + height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y + height / 2, center.Z - depth / 2}
		},
		color,
		{ 0, 1, 0 }
	);

	//Front
	DrawQuads(
		{
			{center.X - width / 2, center.Y - height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y - height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y + height / 2, center.Z + depth / 2},
			{center.X - width / 2, center.Y + height / 2, center.Z + depth / 2}
		},
		color,
		{ 0, 0, 1 }
	);

	//Rear
	DrawQuads(
		{
			{center.X - width / 2, center.Y - height / 2, center.Z - depth / 2},
			{center.X + width / 2, center.Y - height / 2, center.Z - depth / 2},
			{center.X + width / 2, center.Y + height / 2, center.Z - depth / 2},
			{center.X - width / 2, center.Y + height / 2, center.Z - depth / 2}
		},
		color,
		{ 0, 0, -1 }
	);

	//Left
	DrawQuads(
		{
			{center.X - width / 2, center.Y - height / 2, center.Z + depth / 2},
			{center.X - width / 2, center.Y + height / 2, center.Z + depth / 2},
			{center.X - width / 2, center.Y + height / 2, center.Z - depth / 2},
			{center.X - width / 2, center.Y - height / 2, center.Z - depth / 2},
		},
		color,
		{ -1, 0, 0 }
	);

	//Right
	DrawQuads(
		{
			{center.X + width / 2, center.Y - height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y + height / 2, center.Z + depth / 2},
			{center.X + width / 2, center.Y + height / 2, center.Z - depth / 2},
			{center.X + width / 2, center.Y - height / 2, center.Z - depth / 2},
		},
		color,
		{ 1, 0, 0 }
	);
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
		GLuint  PixelFormat;
		static  PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			16,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		parent = wnd;

		hDC = GetDC(wnd->Get());
		PixelFormat = ChoosePixelFormat(hDC, &pfd);

		SetPixelFormat(hDC, PixelFormat, &pfd);
		hRC = wglCreateContext(hDC);

		wglMakeCurrent(hDC, hRC);

		sceneRenderer = renderer;

		Init();
	}

	void AddAmbienLight(RGBAColor color)
	{
		glEnable(GL_LIGHTING);
		//glEnable(GL_COLOR_MATERIAL);
		GLColor clr = RGBToGL(color);
		float params[4] = { clr.R, clr.B, clr.G, clr.A };

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, params);
		glEnable(GL_LIGHT0);
	}

	void Init()
	{
		RECT rect;
		GetClientRect(*parent, &rect);

		glViewport(0, 0, rect.right, rect.bottom);
		ClearColor(0, 0, 0, 255);

		glClearDepth(1.0);
		glDepthFunc(GL_LESS);
		glEnable(GL_NORMALIZE);

		/*glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
		glEnable(GL_POLYGON_SMOOTH);

		glHint(GL_POINT_SMOOTH_HINT, GL_FASTEST);
		glEnable(GL_POINT_SMOOTH);

		glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
		glEnable(GL_LINE_SMOOTH);*/

		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_ALPHA_TEST);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)rect.right / (GLfloat)rect.bottom, 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);

		Render();
	}

	void AddSmooth()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glShadeModel(GL_SMOOTH);
	}

	void ResizeScene(float width, float height)
	{
		RECT rect;
		GetClientRect(*parent, &rect);

		if (height == 0)
			height = 1;

		glViewport(0, 0, width, height);
		ClearColor(0, 0, 0, 255);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)rect.right / (GLfloat)rect.bottom, 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

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

		if (sceneRenderer != nullptr)
			sceneRenderer();
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