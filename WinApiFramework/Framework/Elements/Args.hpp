#pragma once
#include <Windows.h>

struct MainArgs
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance; 
	LPSTR lpCmdLine; 
	int nCmdShow;
	WNDPROC WindowProc;
};

struct CallbackArgs
{
	HWND hWnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
};