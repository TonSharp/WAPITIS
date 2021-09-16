#pragma once

#include "UI.hpp"
#include <vector>

class ListBox : public UI
{

public:

	ListBox(wstring text, Window* parent, HINSTANCE hInstance, bool MultiSelect) : UI(text, parent, hInstance)	
	{
		if (MultiSelect)
			localStyle |= LBS_EXTENDEDSEL;
	}

	void DisableNOScroll()
	{
		localStyle |= LBS_DISABLENOSCROLL;
	}

	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}

	void AddElement(wstring str)
	{
		SendMessage(wnd, LB_ADDSTRING, 0, (LPARAM)str.c_str());
	}
	void AddRange(vector<wstring> items)
	{
		for (auto d : items)
			AddElement(d);
	}

	void RemoveElementByIndex(int index)
	{
		SendMessage(wnd, LB_DELETESTRING, index, 0L);
	}
	void RemoveSelectedElement()
	{
		RemoveElementByIndex(GetSelectedIndex());
	}
	void Clear()
	{
		SendMessage(wnd, LB_RESETCONTENT, 0, 0L);
	}

	void SelectItem(int index)
	{
		SendMessage(wnd, LB_SETCURSEL, index, 0L);
	}
	void SelectItems(int startIndex, int endIndex)
	{
		SendMessage(wnd, LB_SELITEMRANGE, TRUE, MAKELPARAM(startIndex, endIndex));
	}

	int GetSelectedIndex()
	{
		return (int)SendMessage(wnd, LB_GETCURSEL, 0, 0L);
	}
	wstring GetSelectedText()
	{
		wchar_t buff[256];
		auto l = SendMessage(wnd, LB_GETTEXT, GetSelectedIndex(), (LPARAM)buff);

		buff[l] = '\0';

		wstring outp(buff);

		return outp;
	}

	int GetCount()
	{
		return (int)SendMessage(wnd, LB_GETCOUNT, 0, 0L);
	}
	int GetSelectedCount()
	{
		return (int)SendMessage(wnd, LB_GETSELCOUNT, 0, 0L);
	}

	bool IsSelectChanged(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == LBN_SELCHANGE)
			return true;

		return false;
	}
	bool IsDoubleClick(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == LBN_DBLCLK)
			return true;

		else return false;
	}
};