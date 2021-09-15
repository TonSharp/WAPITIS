#pragma once
#include <Windows.h>
#include <vector>
#include "MenuItem.hpp"

using namespace std;

class Menu
{
private:

	HMENU menu;
	wstring name;

	int ID;

	vector<HMENU> subMenus = {};
	vector<int> IDs = {};

public:

	Menu(wstring name, bool isPopup, int ID)
	{
		this->name = name;
		this->ID = ID;

		if (isPopup)
			CreatePopup();
		else
			Create();
	}

	void Create()
	{
		menu = CreateMenu();
	}
	void CreatePopup()
	{
		menu = CreatePopupMenu();

		this->name = name;
	}

	void AddSubMenu(Menu subMenu)
	{
		AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)subMenu.Get(), subMenu.GetName().c_str());

		subMenus.push_back(subMenu.Get());
		IDs.push_back(subMenu.GetID());
	}
	void AddSubMenu(vector<MenuItem> items, int startID, wstring menuName)
	{
		HMENU tempMenu = CreatePopupMenu();
		IDs.push_back(startID);

		for (auto m : items)
		{
			int id = startID;

			AppendMenu(tempMenu, m.Style, id, m.Name.c_str());
			startID++;
		}

		AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)tempMenu, menuName.c_str());

		subMenus.push_back(tempMenu);
	}

	void AddItems(vector<MenuItem> items, int startID)
	{
		for (auto m : items)
		{
			int id = startID;

			AppendMenu(menu, m.Style, startID, m.Name.c_str());
			IDs.push_back(id);

			startID++;
		}
	}

	void Register(HWND wnd)
	{
		SetMenu(wnd, menu);

		for (auto m : subMenus)
		{
			SetMenu(wnd, m);
		}
	}

	DWORD Track(HWND wnd, CallbackArgs args)
	{
		return (DWORD)TrackPopupMenu(menu, TPM_TOPALIGN | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, GET_X_LPARAM(args.lParam), GET_Y_LPARAM(args.lParam), 0, wnd, NULL);
	}

	int GetIDByMenuIndex(int subMenuIndex, int itemIndex)
	{
		if (subMenuIndex >= IDs.size())
			return 0;
		else
			return IDs[subMenuIndex] + itemIndex;
	}

	bool IsClicked(CallbackArgs args, int subMenuIndex, int itemIndex)
	{
		if (this == NULL)
			return false;

		if (subMenuIndex >= IDs.size())
			return false;

		int base = GetIDByMenuIndex(subMenuIndex, itemIndex);

		if (args.Msg != WM_COMMAND)
			return false;

		if (LOWORD(args.wParam) != base)
			return false;

		else
			return true;
	}

	HMENU Get()
	{
		return menu;
	}
	HMENU* GetPointer()
	{
		return &menu;
	}

	wstring GetName()
	{
		return name;
	}

	int GetID()
	{
		return ID;
	}
};