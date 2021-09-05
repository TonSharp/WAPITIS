#pragma once
#include "libs.h"

//Сюда добавляйте свои библиотеки:

wstring szMainClass = L"MainClass 2";
wstring szTitle = L"Laba 2";

int _main_(MainArgs args)
{
    Class* wc = new Class(szMainClass, args.WindowProc, args.hInstance);
    Window* wnd = new Window(szTitle, args.nCmdShow);

    wnd->CreateDefaultWindow(wc);

    return 0;
}

int _callback_(CallbackArgs args)
{
    return 0;
}