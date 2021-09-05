#pragma once
#include "Class.hpp"
#include "Transform.hpp"
#include <string>

using namespace std;

class Window
{
private:

	wstring caption;
	HWND hWindow = NULL;
	int nCmdShow;

	bool Register()
	{
		if (!hWindow)
		{
			MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
			return false;
		}
		else
			Show();
		return true;
	}

public:

	Window(wstring windowCaption, int cmdShow)
	{
		caption = windowCaption;
		nCmdShow = cmdShow;
	}

	bool CreateDefaultWindow(Class* clas)
	{
		hWindow = CreateWindowEx(
			0,
			clas->GetPointer()->lpszClassName,
			caption.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			NULL,
			CW_USEDEFAULT,
			NULL,
			NULL,
			NULL,
			clas->GetPointer()->hInstance,
			NULL
		);

		return Register();
	}

	bool CreateCustomWindow(Class* szClass, DWORD extentedStyle, DWORD style, Transform pos, Transform size, Window* parent, HMENU menu, LPVOID lParam)
	{
		HWND pr = NULL;

		if (parent != NULL)
			pr = parent->Get();

		hWindow = CreateWindowEx(
			extentedStyle,
			szClass->GetPointer()->lpszClassName,
			caption.c_str(),
			style,
			pos.x,
			pos.y,
			size.x,
			size.y,
			pr,
			menu,
			szClass->GetPointer()->hInstance,
			lParam
		);

		return Register();
	}

	void SetCaption(wstring newCaption)
	{
		caption = newCaption;
		SetWindowText(hWindow, caption.c_str());
	}

	void Show()
	{
		ShowWindow(hWindow, nCmdShow);
		Update();
	}
	void Update()
	{
		UpdateWindow(hWindow);
	}

	HWND* GetPointer()
	{
		return &hWindow;
	}
	HWND Get()
	{
		return hWindow;
	}
};