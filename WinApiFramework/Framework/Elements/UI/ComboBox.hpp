#pragma once

#include "UI.hpp"
#include <vector>

using namespace std;

class ComboBox : public UI
{
public:

	// Combo box class.
	ComboBox(wstring text, Window* parent, HINSTANCE hInstance) : UI(text, parent, hInstance)	
	{
	}

	// Shows a disabled horizontal or vertical scroll bar when the combo box does not contain enough items to scroll.
	void DisableNOScroll()
	{
		localStyle |= CBS_DISABLENOSCROLL;
	}

	// Creates a combo box.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"combobox", NULL, WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}

	// Adds an item to the combo box.
	void AddItem(wstring str)
	{
		SendMessage(wnd, CB_ADDSTRING, 0, (LPARAM)str.c_str());
	}
	// Adds several items to the combo box.
	void AddRange(vector<wstring> data)
	{
		for (int i = 0; i < data.size(); i++)
			AddItem(data.at(i));
	}

	// Removes an item by its index.
	void RemoveItemByIndex(int index)
	{
		SendMessage(wnd, CB_DELETESTRING, index, 0L);
	}
	// Removes currently selected item.
	void RemoveSelectedItem()
	{
		RemoveItemByIndex(GetSelectedIndex());
	}
	// Clears the combo box.
	void Clear()
	{
		SendMessage(wnd, CB_RESETCONTENT, 0, 0L);
	}

	// Selects an item from the combo box.
	void SelectItem(int index)
	{
		SendMessage(wnd, CB_SETCURSEL, index, 0L);
	}

	// Returns selected item’s index.
	int GetSelectedIndex()
	{
		return (int)SendMessage(wnd, CB_GETCURSEL, 0, 0L);
	}
	
	// Returns text from an item by its index.
	wstring GetStringByIndex(int index)
	{
		wchar_t buff[512];

		SendMessage(wnd, CB_GETLBTEXT, index, (LPARAM)buff);
		wstring str(buff);

		return str;
	}

	// Returns text from selected item.
	wstring GetSelectedText()
	{
		return GetStringByIndex(GetSelectedIndex());
	}

	// Returns the number of items in the combo box.
	int GetCount()
	{
		return (int)SendMessage(wnd, CB_GETCOUNT, 0, 0L);
	}

	// Returns true if another item was selected.
	bool IsSelectChanged(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == CBN_SELCHANGE)
			return true;

		return false;
	}
	// Returns true if an item was clicked twice.
	bool IsDoubleClick(CallbackArgs args)
	{
		if (args.Msg != WM_COMMAND)
			return false;

		if (args.lParam == (LPARAM)wnd && HIWORD(args.wParam) == CBN_DBLCLK)
			return true;

		else return false;
	}
};