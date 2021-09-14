#pragma once
#include "../Window.hpp"
#include "../Transform.hpp"


#define BORDER WS_BORDER

#define MULTILINE ES_MULTILINE
#define DROPDOWN CBS_DROPDOWN

#define VSCROLL WS_VSCROLL

#define UNRESIZABLE_WINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU)

using namespace std;

class UI
{
protected:

	wstring text;
	HWND wndParent;
	HMENU menu;
	HINSTANCE hInstance;
	LPVOID lParam;

	HWND wnd;

public:

	UI(wstring text, HWND parent, int id, HINSTANCE hInstance, LPVOID lParam)
	{
		this->text = text;

		if (parent != NULL)
			wndParent = parent;

		this->menu = (HMENU)id;
		this->hInstance = hInstance;
		this->lParam = lParam;
	}

	virtual void Create(DWORD style, Transform pos, Transform size)
	{
	}

	bool IsContextMenu(CallbackArgs args)
	{
		if (args.Msg == WM_CONTEXTMENU && (HWND)args.wParam == wnd)
			return true;
		else
			return false;
	}

	HWND Get()
	{
		return wnd;
	}

	HWND* GetPointer()
	{
		return &wnd;
	}
};