#pragma once

#include "UI.hpp"

class Text : public UI
{
public:

	Text(wstring text, HWND parent, int id, HINSTANCE hInstance, LPVOID lParam) : UI(text, parent, id, hInstance, lParam)	
	{
	}

	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"static", text.c_str(), WS_CHILD | WS_VISIBLE | style, pos.x, pos.y, size.x, size.y, wndParent, menu, hInstance, lParam);
	}
};