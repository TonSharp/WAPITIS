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

	// Window class.
	Window(wstring caption, wstring* className, MainArgs args)
	{
		mainArgs = args;

		this->caption = caption;
		this->className = className;

		wnd = new WindowClass(*className);
		wnd->InitDefaulClass(args.hInstance);
	}

	// Returns a registered class.
	bool RegClass()
	{
		if (isClassRegistered)
			return false;

		isClassRegistered = wnd->Register();
		return isClassRegistered;
	}

	// Creates an empty resizeable window. Mostly useful for testing purposes.
	bool CreateDefaultWindow(HWND parent, int (*callback)(CallbackArgs args))
	{
		if (!isClassRegistered)
			RegClass();

		DestroyWindow(hWnd);

		hWnd = CreateWindow(
			className->c_str(),
			caption.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, 0,
			CW_USEDEFAULT, 0,
			parent,
			NULL,
			mainArgs.hInstance,
			NULL
		);

		SetWindowLong(hWnd, GWL_USERDATA, (LONG)callback);

		return RegisterWindow();
	}

	// Creates a window with specified parameters.
	bool CreateCustomWindow(DWORD extentedStyle, DWORD style, Transform pos, Transform size, HWND parent, HMENU menu, LPVOID lParam, int (*callback)(CallbackArgs args))
	{
		if (!isClassRegistered)
			RegClass();

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

	// Makes the window active.
	void Enable()
	{
		EnableWindow(hWnd, true);
	}
	// Makes the window inactive.
	void Disable()
	{
		EnableWindow(hWnd, false);
	}
	// Enables (disables) the window so it can (not) be used.
	void SetEnableState(bool state)
	{
		EnableWindow(hWnd, state);
	}

	// Sets window’s caption.
	void SetCaption(wstring newCaption)
	{
		caption = newCaption;
		SetWindowText(hWnd, caption.c_str());
	}
	// Sets the window’s background color.
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

	// Shows the window on screen.
	void Show()
	{
		ShowWindow(hWnd, mainArgs.nCmdShow);
		Update();
	}
	// Updates the client area of the window.
	void Update()
	{
		UpdateWindow(hWnd);
	}

	// Prepares the window for painting.
	void StartDraw()
	{
		BeginPaint(hWnd, &ps);
	}
	// Marks the end of painting in the window.
	void StopDraw()
	{
		EndPaint(hWnd, &ps);
	}

	// Returns true if painting is in process.
	bool IsDraw(CallbackArgs args)
	{
		if (args.Msg == WM_PAINT)
			return true;
		else
			return false;
	}
	// Returns true if the window is being resized.
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
	// Returns true if a specified key is pressed.
	bool IsKeyDown(CallbackArgs args, DWORD key)
	{
		if (args.Msg != WM_KEYDOWN)
			return false;

		if (key == 0)
			return true;

		if (args.wParam == key)
			return true;
		else
			return false;
	}
	// Returns true if a specified key is released.
	bool IsKeyUp(CallbackArgs args, DWORD key)
	{
		if (args.Msg != WM_KEYUP)
			return false;

		if (key == 0)
			return true;

		if (args.wParam == key)
			return true;
		else
			return false;
	}
	// Returns true if window is created.
	bool IsCreate(CallbackArgs args)
	{
		if (args.Msg == WM_CREATE)
			return true;
		return false;
	}

	// Returns a pointer to the window.
	HWND* GetPointer()
	{
		return &hWnd;
	}
	// Returns window as HWND.
	HWND Get()
	{
		return hWnd;
	}
	// Returns a pointer to the window’s class.
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