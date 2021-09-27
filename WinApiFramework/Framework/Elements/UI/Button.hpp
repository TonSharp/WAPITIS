#pragma once

#include "ButtonBase.hpp"

class Button : public ButtonBase
{
public:
	// Button class.
	Button(wstring text, Window* parent, HINSTANCE hInstance) : ButtonBase(text, parent, hInstance)	
	{
	}

	// Creates a button.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"button", text.c_str(), WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}
};