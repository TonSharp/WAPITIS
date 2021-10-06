#pragma once
#include "Elements/Args.hpp"

class Keyboard
{
private:

public:

	static bool GetKeyDown(CallbackArgs args, DWORD KeyCode)
	{
		if (args.Msg != WM_KEYDOWN)
			return false;

		if (args.wParam == KeyCode)
			return true;

		return false;
	}
	static bool GetKeyDown(CallbackArgs args)
	{
		return args.Msg == WM_KEYDOWN;
	}

	static bool GetKeyUp(CallbackArgs args, DWORD KeyCode)
	{
		if (args.Msg != WM_KEYUP)
			return false;

		if (args.wParam == KeyCode)
			return true;

		return false;
	}
	static bool GetKeyUp(CallbackArgs args)
	{
		return args.Msg == WM_KEYUP;
	}
};