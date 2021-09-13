#pragma once
#include <Windows.h>

struct MainArgs
{
	HINSTANCE hInstance;
	HINSTANCE hPrevInstance; 
	LPSTR lpCmdLine; 
	int nCmdShow;
};

struct CallbackArgs
{
	HWND hWnd;
	UINT Msg;
	WPARAM wParam;
	LPARAM lParam;
};