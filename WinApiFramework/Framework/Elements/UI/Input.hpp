#pragma once

#include "UI.hpp"

class Input : public UI
{
public:

	Input(wstring text, Window* parent, HINSTANCE hInstance) : UI(text, parent, hInstance)	
	{
	}

	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"edit", text.c_str(), WS_CHILD | WS_VISIBLE | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}

	void LimitText(int maxCount)
	{
		SendMessage(wnd, EM_LIMITTEXT, maxCount, 0L);
	}
	void MultiLine()
	{
		localStyle |= ES_MULTILINE;
	}

	void AddVScroll() override
	{
		localStyle |= ES_AUTOVSCROLL;
	}
	void AddHScroll() override
	{
		localStyle |= ES_AUTOHSCROLL;
	}

	void LeftAlign()
	{
		localStyle |= ES_LEFT;
	}
	void CenterAlign()
	{
		localStyle |= ES_CENTER;
	}
	void RightAligin()
	{
		localStyle |= ES_RIGHT;
	}

	void Lowercase()
	{
		localStyle |= ES_LOWERCASE;
	}
	void Uppercase()
	{
		localStyle |= ES_UPPERCASE;
	}

	void Number()
	{
		localStyle |= ES_NUMBER;
	}
	void Password()
	{
		localStyle |= ES_PASSWORD;
	}

	void ReadOnly()
	{
		localStyle |= ES_READONLY;
	}

	wstring GetLine(int line)
	{
		wchar_t buff[256];
		buff[0] = 256;

		auto count = SendMessage(wnd, EM_GETLINE, line, (LPARAM)(&buff));
		buff[count] = '\0';

		wstring outp(buff);

		return outp;
	}
	int GetLinesCount()
	{
		return (int)SendMessage(wnd, EM_GETLINECOUNT, 0, 0L);
	}

	bool IsChaged(CallbackArgs args)
	{
		if (args.Msg == EN_CHANGE && args.lParam == (LPARAM)wnd)
			return true;
		else
			return false;
	}
};