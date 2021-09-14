#pragma once

#include "UI.hpp"
#include <vector>

using namespace std;

class ComboBox : public UI
{
public:

	ComboBox(wstring text, HWND parent, int id, HINSTANCE hInstance, LPVOID lParam) : UI(text, parent, id, hInstance, lParam)	
	{
	}

	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"combobox", NULL, WS_CHILD | WS_VISIBLE | style, pos.x, pos.y, size.x, size.y, wndParent, menu, hInstance, lParam);
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

	wstring GetSelectedString()
	{
		return GetStringByIndex(GetSelectedIndex());
	}

	void SelectElement(int index)
	{
		SendMessage(wnd, CB_SETCURSEL, index, NULL);
	}
};