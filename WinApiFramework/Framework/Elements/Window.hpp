#pragma once
#include "Transform.hpp"
#include "Args.hpp"
#include "WindowClass.hpp"
#include <string>

using namespace std;

bool Closing(CallbackArgs args)
{
	return args.Msg == WM_CLOSE;
}

void Quit()
{
	PostQuitMessage(0);
}

class Window
{
private:

	MainArgs mainArgs;

	wstring caption;
	wstring* className;

	HWND hWnd;

	WindowClass* wnd;

	bool isClassRegistered = false;

	PAINTSTRUCT ps;

	bool RegisterWindow()
	{
		if (!hWnd)
		{
			MessageBox(NULL, L"Не удалось создать окно!", L"Ошибка", MB_OK);
			return false;
		}
		else
			Show();
		return true;
	}

public:

	Window(wstring caption, wstring* className, MainArgs args)
	{
		mainArgs = args;

		this->caption = caption;
		this->className = className;

		wnd = new WindowClass(*className);
		wnd->InitDefaulClass(args.hInstance);
	}

	bool RegisterClass()
	{
		if (isClassRegistered)
			return false;
		
		isClassRegistered = wnd->Register();
		return isClassRegistered;
	}

	bool CreateDefaultWindow(HWND parent, int (*callback)(CallbackArgs args))
	{
		if (!isClassRegistered)
			RegisterClass();

		DestroyWindow(hWnd);

		hWnd = CreateWindow(
			className->c_str(),
			caption.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			NULL,
			CW_USEDEFAULT,
			NULL,
			parent,
			NULL,
			mainArgs.hInstance,
			NULL
		);

		SetWindowLong(hWnd, GWL_USERDATA, (LONG)callback);

		return RegisterWindow();
	}

	bool CreateCustomWindow(DWORD extentedStyle, DWORD style, Transform pos, Transform size, HWND parent, HMENU menu, LPVOID lParam, int (*callback)(CallbackArgs args))
	{
		if (!isClassRegistered)
			RegisterClass();

		DestroyWindow(hWnd);

		hWnd = CreateWindowEx(
			extentedStyle,
			className->c_str(),
			caption.c_str(),
			style,
			pos.x,
			pos.y,
			size.x,
			size.y,
			parent,
			menu,
			mainArgs.hInstance,
			lParam
		);

		SetWindowLong(hWnd, GWL_USERDATA, (LONG)callback);

		return RegisterWindow();
	}

	void Enable()
	{
		EnableWindow(hWnd, true);
	}
	void Disable()
	{
		EnableWindow(hWnd, false);
	}
	void SetEnableState(bool state)
	{
		EnableWindow(hWnd, state);
	}

	void SetCaption(wstring newCaption)
	{
		caption = newCaption;
		SetWindowText(hWnd, caption.c_str());
	}
	void SetBackgroundColor(COLORREF color)
	{
		if(!isClassRegistered)
			wnd->SetBackgroundColor(color);
		else
		{
			HBRUSH brush = CreateSolidBrush(color);
			SetClassLong(hWnd, GCLP_HBRBACKGROUND, (LONG)brush);
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}

	void Show()
	{
		ShowWindow(hWnd, mainArgs.nCmdShow);
		Update();
	}
	void Update()
	{
		UpdateWindow(hWnd);
	}

	void StartDraw()
	{
		BeginPaint(hWnd, &ps);
	}
	void StopDraw()
	{
		EndPaint(hWnd, &ps);
	}

	bool IsDraw(CallbackArgs args)
	{
		if (args.Msg == WM_PAINT)
			return true;
		else
			return false;
	}
	bool IsResize(float* width, float* height, CallbackArgs args)
	{
		if (args.Msg == WM_SIZE)
		{
			*width = LOWORD(args.lParam);
			*height = HIWORD(args.lParam);

			return true;
		}
		
		return false;
	}
	bool IsCreate(CallbackArgs args)
	{
		if (args.Msg == WM_CREATE)
			return true;
		return false;
	}

	HWND* GetPointer()
	{
		return &hWnd;
	}
	HWND Get()
	{
		return hWnd;
	}
	WindowClass* GetClassPointer()
	{
		return wnd;
	}

	operator HWND() const
	{
		return hWnd;
	}
	operator WindowClass* () const
	{
		return wnd;
	}
};