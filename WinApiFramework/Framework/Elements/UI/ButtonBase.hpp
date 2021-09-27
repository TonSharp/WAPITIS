#pragma once

#include "UI.hpp"

class ButtonBase : public UI
{
public:

	ButtonBase(wstring text, Window* parent, HINSTANCE hInstance) : UI(text, parent, hInstance)	
	{
	}

	virtual void Create(DWORD style, Transform pos, Transform size)
	{
	}

	// Sets highlight state of a button. The highlight state indicates whether the button is highlighted as if the user had pushed it.
	virtual void SetState(bool state)
	{
		if (this == nullptr)
			return;

		SendMessage(wnd, BM_SETSTATE, state, 0);
	}

	// Sets the check state of a radio button or check box.
	virtual void SetCheck(bool check)
	{
		if (this == nullptr)
			return;

		int val = 0;

		if (check)
			val = 1;

		SendMessage(wnd, BM_SETCHECK, val, 0);
	}

	// Returns true if radio button or check box is checked.
	virtual bool IsChecked()
	{
		if (this == nullptr)
			return false;

		WORD res = (WORD)SendMessage(wnd, BM_GETCHECK, 0, 0);

		if (res == 0 || res == 2)
			return false;
		else
			return true;
	}

	// Returns true if the button is clicked.
	virtual bool IsClicked(CallbackArgs args)
	{
		if (this == nullptr)
			return false;

		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd)
			return true;
		else 
			return false;
	}
};