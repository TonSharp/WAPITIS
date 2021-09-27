#pragma once

#include "UI.hpp"

class Text : public UI
{
public:

	// Text class.
	Text(wstring text, Window* parent, HINSTANCE hInstance) : UI(text, parent, hInstance)	
	{
	}

	// Draws text in the current window.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"static", text.c_str(), WS_CHILD | WS_VISIBLE | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}
};