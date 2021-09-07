#pragma once

#include "ButtonBase.hpp"

class CheckBox3 : public ButtonBase
{
public:

	CheckBox3(wstring text, Window* parent, int id, HINSTANCE hInstance, LPVOID lParam) : ButtonBase(text, parent, id, hInstance, lParam)	
	{
	}

	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"button", text.c_str(), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE | style, pos.x, pos.y, size.x, size.y, *wndParent, menu, hInstance, lParam);
	}
};