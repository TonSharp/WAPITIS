#pragma once

#include "UI.hpp"

class ButtonBase : public UI
{
public:

	ButtonBase(wstring text, HWND parent, int id, HINSTANCE hInstance, LPVOID lParam) : UI(text, parent, id, hInstance, lParam)	
	{
	}

	virtual void Create(DWORD style, Transform pos, Transform size)
	{
	}

	virtual void SetState(bool state)
	{
		if (this == nullptr)
			return;

		SendMessage(wnd, BM_SETSTATE, state, NULL);
	}

	virtual void SetCheck(bool check)
	{
		if (this == nullptr)
			return;

		int val = 0;

		if (check)
			val = 1;

		SendMessage(wnd, BM_SETCHECK, val, NULL);
	}

	virtual bool IsChecked()
	{
		if (this == nullptr)
			return false;

		WORD res = (WORD)SendMessage(wnd, BM_GETCHECK, NULL, NULL);

		if (res == 0 || res == 2)
			return false;
		else
			return true;
	}

	virtual bool IsClicked(CallbackArgs args)
	{
		if (this == nullptr)
			return false;

		if (args.Msg != WM_COMMAND)
			return false;

		if (LOWORD(args.wParam) == (int)menu)
			return true;
		else 
			return false;
	}
};