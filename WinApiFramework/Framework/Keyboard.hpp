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

		else
			return false;
	}
};