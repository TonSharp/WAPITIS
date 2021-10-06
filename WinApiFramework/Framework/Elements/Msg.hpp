#pragma once
#include <Windows.h>

class Msg
{
private:

	MSG msg;

public:

	BOOL Get()
	{
		return GetMessage(&msg, nullptr, 0, 0);
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