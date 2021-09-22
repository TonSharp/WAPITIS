#pragma once

#include "ButtonBase.hpp"

class RadioButton : public ButtonBase
{
public:

	// Radio button class.
	RadioButton(wstring text, Window* parent, HINSTANCE hInstance) : ButtonBase(text, parent, hInstance)	
	{
	}

	// Creates a radio button.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"button", text.c_str(), WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}
};