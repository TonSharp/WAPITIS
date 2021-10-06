#pragma once
#include "Elements/Args.hpp"

class Mouse
{
private:

	static float x, y;
	static float dx, dy;

	static bool cursorLock;
	static Window* linkedWindow;

public:

	static void LockCursor()
	{
		cursorLock = true;

		if (linkedWindow != nullptr)
			SetCapture(linkedWindow->Get());
	}
	static void UnlockCursor()
	{
		cursorLock = false;
		ReleaseCapture();
	}
	static void SetCursorLock(bool lock)
	{
		cursorLock = lock;

		if (cursorLock && linkedWindow != NULL)
			SetCapture(linkedWindow->Get());
	}

	static void Link(Window* wnd)
	{
		linkedWindow = wnd;

		if (cursorLock)
			SetCapture(linkedWindow->Get());
	}

	static void Update()
	{
		RECT rect;

		auto point = new POINT();
		GetCursorPos(point);

		float centerX = point->x;
		float centerY = point->y;

		if (linkedWindow != nullptr)
		{
			GetWindowRect(linkedWindow->Get(), &rect);

			centerX = (rect.right - rect.left) / 2;
			centerY = (rect.bottom - rect.top) / 2;
		}

		dx = x - point->x;
		dy = point->y - y;

		x = point->x;
		y = point->y;

		if (cursorLock && linkedWindow != nullptr && GetFocus() == linkedWindow->Get())
			SetCursorPos(centerX, centerY);

		x = centerX;
		y = centerY;
	}

	static float GetDX()
	{
		return dx;
	}
	static float GetDY()
	{
		return dy;
	}

	static void HideCursor()
	{
		ShowCursor(FALSE);
	}
	static void SetCursorVisiblity(bool visible)
	{
		ShowCursor(visible);
	}

	static bool IsLeftButtonDown(CallbackArgs args)
	{
		return args.Msg == WM_LBUTTONDOWN;
	}
	static bool IsLeftButtonUp(CallbackArgs args)
	{
		return args.Msg == WM_LBUTTONUP;
	}
	static bool IsLeftDoubleClick(CallbackArgs args)
	{
		return args.Msg == WM_LBUTTONDBLCLK;
	}

	static bool IsRightButtodDown(CallbackArgs args)
	{
		return args.Msg == WM_RBUTTONDOWN;
	}
	static bool IsRightButtonUp(CallbackArgs args)
	{
		return args.Msg == WM_RBUTTONUP;
	}
	static bool IsRightDoubleClick(CallbackArgs args)
	{
		return args.Msg == WM_RBUTTONDBLCLK;
	}
};

bool Mouse::cursorLock = false;

float Mouse::dx = 0;
float Mouse::dy = 0;

float Mouse::x = 0;
float Mouse::y = 0;

Window* Mouse::linkedWindow = nullptr;