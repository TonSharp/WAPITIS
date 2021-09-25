#pragma once

#include "UI.hpp"
#include <vector>

class ListBox : public UI
{

public:
	// List box class.
	ListBox(wstring text, Window* parent, HINSTANCE hInstance, bool MultiSelect) : UI(text, parent, hInstance)	
	{
		if (MultiSelect)
			localStyle |= LBS_EXTENDEDSEL;
	}

	// Shows a disabled horizontal or vertical scroll bar when the list box does not contain enough items to scroll.
	void DisableNOScroll()
	{
		localStyle |= LBS_DISABLENOSCROLL;
	}

	// Creates a list box.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}

	// Adds an item to the list box.
	void AddItem(wstring str)
	{
		SendMessage(wnd, LB_ADDSTRING, 0, (LPARAM)str.c_str());
	}
	// Adds several items to the list box.
	void AddRange(vector<wstring> items)
	{
		for (auto d : items)
			AddItem(d);
	}

	// Removes an item by its index.
	void RemoveItemByIndex(int index)
	{
		SendMessage(wnd, LB_DELETESTRING, index, 0L);
	}
	// Removes currently selected items.
	void RemoveSelectedItems()
	{
		int buff[50];
		int selectedItems = SendMessage(wnd, LB_GETSELITEMS, 10, (LPARAM) buff); //Moves 10 selected items in buff
		for (int i = selectedItems - 1; i >= 0; i--) {
			SendMessage(wnd, LB_DELETESTRING, buff[i], 0);
		}
	}
	// Clears the list box.
	void Clear()
	{
		SendMessage(wnd, LB_RESETCONTENT, 0, 0L);
	}

	// Selects an item from the list box.
	void SelectItem(int index)
	{
		SendMessage(wnd, LB_SETCURSEL, index, 0L);
	}
	// Selects several items from the list box.
	void SelectItem(int startIndex, int endIndex)
	{
		SendMessage(wnd, LB_SELITEMRANGE, TRUE, MAKELPARAM(startIndex, endIndex));
	}

	// Returns selected item’s index.
	int GetSelectedIndex()
	{
		return (int)SendMessage(wnd, LB_GETCURSEL, 0, 0L);
	}
	// Returns text from selected item.
	wstring GetSelectedText()
	{
		wchar_t buff[256];
		auto l = SendMessage(wnd, LB_GETTEXT, GetSelectedIndex(), (LPARAM)buff);

		buff[l] = '\0';

		wstring outp(buff);

		return outp;
	}

	// Returns the number of items in the list box.
	int GetCount()
	{
		return (int)SendMessage(wnd, LB_GETCOUNT, 0, 0L);
	}
	// Returns the number of selected items.
	int GetSelectedCount()
	{
		return (int)SendMessage(wnd, LB_GETSELCOUNT, 0, 0L);
	}

	// Returns true if selected item has changed.
	bool IsSelectChanged(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == LBN_SELCHANGE)
			return true;

		return false;
	}
	// Returns true if an item was clicked twice.
	bool IsDoubleClick(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == LBN_DBLCLK)
			return true;

		else return false;
	}
};