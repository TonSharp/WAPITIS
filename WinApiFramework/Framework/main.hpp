#pragma once
#include "libs.hpp"

//Сюда добавляйте свои библиотеки:

wstring szMainClass = L"MainClass";
wstring szTitle = L"Title";

Window* wnd;

int MainCallback(CallbackArgs);

int _main_(MainArgs args)
{
    wnd = new Window(szTitle, &szMainClass, args);
    wnd->CreateDefaultWindow(NULL, MainCallback);
    wnd->SetBackgroundColor(RGB(100, 100, 100));

    return 0;
}

int MainCallback(CallbackArgs args)
{
    if (Closing(args))
        Quit();

    return 1;
}