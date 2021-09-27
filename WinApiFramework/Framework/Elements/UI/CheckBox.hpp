#pragma once

#include "ButtonBase.hpp"

class CheckBox : public ButtonBase
{
public:
	// Check box class.
	CheckBox(wstring text, Window* parent, HINSTANCE hInstance) : ButtonBase(text, parent, hInstance)	
	{
	}

	// Creates a check box.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"button", text.c_str(), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX |  style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}
};