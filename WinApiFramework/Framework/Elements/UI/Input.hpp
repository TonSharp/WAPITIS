#pragma once

#include "UI.hpp"

class Input : public UI
{
public:

	// Input class.
	Input(wstring text, Window* parent, HINSTANCE hInstance) : UI(text, parent, hInstance)	
	{
	}

	// Creates an input field.
	void Create(DWORD style, Transform pos, Transform size) override
	{
		wnd = CreateWindow(L"edit", text.c_str(), WS_CHILD | WS_VISIBLE | style | localStyle, pos.x, pos.y, size.x, size.y, wndParent->Get(), NULL, hInstance, NULL);
	}

	// Sets the text limit.
	void LimitText(int maxCount)
	{
		SendMessage(wnd, EM_LIMITTEXT, maxCount, 0L);
	}
	// Designates a multiline input.
	void MultiLine()
	{
		localStyle |= ES_MULTILINE;
	}

	// Adds vertical scroll.
	void AddVScroll() override
	{
		localStyle |= ES_AUTOVSCROLL;
	}
	// Adds horizontal scroll.
	void AddHScroll() override
	{
		localStyle |= ES_AUTOHSCROLL;
	}

	// Aligns text with the left margin.
	void LeftAlign()
	{
		localStyle |= ES_LEFT;
	}
	// Centers text.
	void CenterAlign()
	{
		localStyle |= ES_CENTER;
	}
	// Aligns text with the right margin.
	void RightAligin()
	{
		localStyle |= ES_RIGHT;
	}

	// Converts all characters to lowercase.
	void Lowercase()
	{
		localStyle |= ES_LOWERCASE;
	}
	// Converts all characters to uppercase.
	void Uppercase()
	{
		localStyle |= ES_UPPERCASE;
	}

	// Allows only digits to be entered.
	void Number()
	{
		localStyle |= ES_NUMBER;
	}
	// Displays an asterisk (*) for each character typed.
	void Password()
	{
		localStyle |= ES_PASSWORD;
	}

	// Prevents the user from typing or editing text.
	void ReadOnly()
	{
		localStyle |= ES_READONLY;
	}

	// Returns the text from input field.
	wstring GetLine(int line)
	{
		wchar_t buff[256];
		buff[0] = 256;

		auto count = SendMessage(wnd, EM_GETLINE, line, (LPARAM)(&buff));
		buff[count] = '\0';

		wstring outp(buff);

		return outp;
	}
	// Returns the number of lines in a multiline input.
	int GetLinesCount()
	{
		return (int)SendMessage(wnd, EM_GETLINECOUNT, 0, 0L);
	}

	// Returns true if text inside the input has changed.
	bool IsChaged(CallbackArgs args)
	{
		if (args.Msg == EN_CHANGE && args.lParam == (LPARAM)wnd)
			return true;
		else
			return false;
	}
};