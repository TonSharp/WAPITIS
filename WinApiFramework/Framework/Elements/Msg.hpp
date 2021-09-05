#pragma once
#include <Windows.h>

class Msg
{
private:

	MSG msg;

public:

	BOOL Get()
	{
		return GetMessage(&msg, NULL, NULL, NULL);
	}

	void Dispatch()
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	WPARAM wParam()
	{
		return msg.wParam;
	}
};