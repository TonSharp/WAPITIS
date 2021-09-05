#pragma once
#include <windows.h>
#include <string>

using namespace std;

class Class
{
private:

	wstring szClassName;
	WNDCLASSEX wndClass = {0};

	void Register()
	{
		if (!RegisterClassEx(&wndClass))
			MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
	}

public:

	Class(wstring className)
	{
		szClassName = className;
	}

	Class(wstring className, WNDPROC callback, HINSTANCE hInstance)
	{
		szClassName = className;
		CreateDefaultClass(callback, hInstance);
	}

	void CreateDefaultClass(WNDPROC callback, HINSTANCE hInstance)
	{
		wndClass.cbSize = sizeof(WNDCLASSEX); // размер структуры (в байтах)
		wndClass.style = CS_HREDRAW | CS_VREDRAW; // стиль класса окошка
		wndClass.lpfnWndProc = callback; // указатель на пользовательскую функцию
		wndClass.lpszMenuName = NULL; // указатель на имя меню (у нас его нет)
		wndClass.lpszClassName = szClassName.c_str(); // указатель на имя класса
		wndClass.cbWndExtra = NULL; // число освобождаемых байтов в конце структуры
		wndClass.cbClsExtra = NULL; // число освобождаемых байтов при создании экземпляра приложения
		wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO); // декриптор пиктограммы
		wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // дескриптор маленькой пиктограммы (в трэе)
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // дескриптор курсора
		wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // дескриптор кисти для закраски фона окна
		wndClass.hInstance = hInstance;

		Register();
	}

	WNDCLASSEX* GetPointer()
	{
		return &wndClass;
	}
};