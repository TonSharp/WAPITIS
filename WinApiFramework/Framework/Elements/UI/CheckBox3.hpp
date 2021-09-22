#pragma once

#include "ButtonBase.hpp"

class CheckBox3 : public ButtonBase
{
public:

	// Three-state check box class.
	CheckBox3(wstring text, Window* parent, HINSTANCE hInstance) : ButtonBase(text, parent, hInstance)	
	{
	}

	// Creates a three-state check box.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"button", text.c_str(), WS_CHILD | WS_VISIBLE | BS_AUTO3STATE | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}
};