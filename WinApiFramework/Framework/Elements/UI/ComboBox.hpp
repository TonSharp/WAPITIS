#pragma once

#include "UI.hpp"
#include <vector>

using namespace std;

class ComboBox : public UI
{
public:

	ComboBox(wstring text, Window* parent, HINSTANCE hInstance) : UI(text, parent, hInstance)	
	{
	}

	void DisableNOScroll()
	{
		localStyle |= CBS_DISABLENOSCROLL;
	}

	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"combobox", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}

	void AddElement(wstring str)
	{
		SendMessage(wnd, CB_ADDSTRING, 0, (LPARAM)str.c_str());
	}
	void AddRange(vector<wstring> data)
	{
		for (int i = 0; i < data.size(); i++)
			AddElement(data.at(i));
	}

	void RemoveElementByIndex(int index)
	{
		SendMessage(wnd, CB_DELETESTRING, index, 0L);
	}
	void RemoveSelectedElement()
	{
		RemoveElementByIndex(GetSelectedIndex());
	}
	void Clear()
	{
		SendMessage(wnd, CB_RESETCONTENT, 0, 0L);
	}

	void SelectItem(int index)
	{
		SendMessage(wnd, CB_SETCURSEL, index, 0L);
	}

	int GetSelectedIndex()
	{
		return (int)SendMessage(wnd, CB_GETCURSEL, 0, 0L);
	}
	
	wstring GetStringByIndex(int index)
	{
		wchar_t buff[512];

		SendMessage(wnd, CB_GETLBTEXT, index, (LPARAM)buff);
		wstring str(buff);

		return str;
	}

	wstring GetSelectedText()
	{
		return GetStringByIndex(GetSelectedIndex());
	}

	int GetCount()
	{
		return (int)SendMessage(wnd, CB_GETCOUNT, 0, 0L);
	}

	bool IsSelectChanged(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == CBN_SELCHANGE)
			return true;

		return false;
	}
	bool IsDoubleClick(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == CBN_DBLCLK)
			return true;

		else return false;
	}
};