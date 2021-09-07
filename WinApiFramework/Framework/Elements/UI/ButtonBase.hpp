#pragma once

#include "UI.hpp"

class ButtonBase : public UI
{
public:

	ButtonBase(wstring text, Window* parent, int id, HINSTANCE hInstance, LPVOID lParam) : UI(text, parent, id, hInstance, lParam)	
	{
	}

	virtual void Create(DWORD style, Transform pos, Transform size)
	{
	}

	virtual void SetState(bool state)
	{
		SendMessage(wnd, BM_SETSTATE, state, NULL);
	}

	virtual void SetCheck(bool check)
	{
		int val = 0;

		if (check)
			val = 1;

		SendMessage(wnd, BM_SETCHECK, val, NULL);
	}

	virtual bool IsChecked()
	{
		WORD res = (WORD)SendMessage(wnd, BM_GETCHECK, NULL, NULL);

		if (res == 0 || res == 2)
			return false;
		else
			return true;
	}

	virtual bool IsClicked(WPARAM wParam, UINT msg)
	{
		if (msg != WM_COMMAND)
			return false;

		if (LOWORD(wParam) == (int)menu)
			return true;
		else 
			return false;
	}
};