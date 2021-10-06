#pragma once
#include <windows.h>
#include <string>
#include "Args.hpp"

using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	auto customProc = (int(*)(CallbackArgs))GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (customProc != nullptr)
		if (customProc({ hWnd, Msg, wParam, lParam }) != 1) {}

	if (Msg == WM_CLOSE)
		DestroyWindow(hWnd);

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}

class WindowClass
{
private:

	wstring szClassName;
	WNDCLASSEX wndClass = {0};

	bool RegisterWindowClass()
	{
		if (!RegisterClassEx(&wndClass))
		{
			MessageBox(nullptr, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
			auto err = GetLastError();
			return false;
		}

		return true;
	}

	int (*UserCallback)(CallbackArgs);

public:

	WindowClass(wstring text)
	{
		szClassName = text;
	}

	void InitDefaulClass(HINSTANCE hInstance)
	{
		wndClass = { 0 };

		wndClass.cbSize = sizeof(WNDCLASSEX);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = szClassName.c_str();
		wndClass.cbWndExtra = 0;
		wndClass.cbClsExtra = 0;
		wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wndClass.hInstance = hInstance;
	}

	bool Register()
	{
		return RegisterWindowClass();
	}

	void SetClassStyle(DWORD classStyle, COLORREF bgColor)
	{
		wndClass.style = CS_HREDRAW | CS_VREDRAW | classStyle;
	}
	void SetBackgroundColor(COLORREF bgColor)
	{
		wndClass.hbrBackground = CreateSolidBrush(bgColor);
	}

	WNDCLASSEX* GetPointer()
	{
		return &wndClass;
	}
	WNDCLASSEX Get()
	{
		return wndClass;
	}

	operator WNDCLASSEX() const
	{
		return wndClass;
	}
};