#pragma once
#include "Elements/Args.hpp"

class Mouse
{
private:

	static float x, y;
	static float dx, dy;

	static bool cursorLock;

public:

	static void LockCursor();
	static void UnlockCursor();
	static void SetCursorLock(bool lock);

	static void Update(Window* wnd);

	static float GetDX();
	static float GetDY();

	static void HideCursor()
	{
		ShowCursor(FALSE);
	}
	static void SetCursorCisiblity(bool visible)
	{
		ShowCursor(visible);
	}
};

bool Mouse::cursorLock = false;

float Mouse::dx = 0;
float Mouse::dy = 0;

float Mouse::x = 0;
float Mouse::y = 0;

float Mouse::GetDX()
{
	auto dx = Mouse::dx;
	return dx;
}
float Mouse::GetDY()
{
	auto dy = Mouse::dy;
	return dy;
}

void Mouse::LockCursor()
{
	Mouse::cursorLock = true;
}
void Mouse::UnlockCursor()
{
	Mouse::cursorLock = false;
}
void Mouse::SetCursorLock(bool lock)
{
	Mouse::cursorLock = lock;
}

void Mouse::Update(Window* wnd)
{
	RECT rect;
	GetWindowRect(wnd->Get(), &rect);

	float centerX = (rect.right - rect.left) / 2;
	float centerY = (rect.bottom - rect.top) / 2;

	LPPOINT point = new POINT();
	GetCursorPos(point);

	dx = x - point->x;
	dy = point->y - y;

	x = point->x;
	y = point->y;

	if (cursorLock)
		SetCursorPos(centerX, centerY);

	x = centerX;
	y = centerY;
}