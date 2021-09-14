#pragma once

#include "UI.hpp"

class ListBox : public UI
{
public:

	ListBox(wstring text, HWND parent, int id, HINSTANCE hInstance, LPVOID lParam) : UI(text, parent, id, hInstance, lParam)	
	{
	}

	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | style, pos.x, pos.y, size.x, size.y, wndParent, menu, hInstance, lParam);
	}

	void AddElement(wstring str)
	{
		SendMessage(wnd, LB_ADDSTRING, 0, (LPARAM)str.c_str());
	}

	void RemoveElementByIndex(int index)
	{
		SendMessage(wnd, LB_DELETESTRING, index, NULL);
	}
	void RemoveSelectedElement()
	{
		RemoveElementByIndex(GetSelectedIndex());
	}

	int GetSelectedIndex()
	{
		return (int)SendMessage(wnd, LB_GETCURSEL, 0, 0L);
	}

	bool IsLeftDoubleClick(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (LOWORD(args.wParam) == (int)menu && HIWORD(args.wParam) == LBN_DBLCLK)
			return true;

		else return false;
	}
};