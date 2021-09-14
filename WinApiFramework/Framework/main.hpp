#pragma once
#include "libs.h"

//Сюда добавляйте свои библиотеки:

wstring szMainClass = L"MainClass";
wstring szEditClass = L"EditClass";
wstring szTitle = L"Laba 5";

Window* wnd;
Window* editWnd;

ListBox* list;

Menu* mainMenu;
Menu* listContext;

static int MainCallback(CallbackArgs);
static int EditCallback(CallbackArgs);

int _main_(MainArgs args)
{
    wnd = new Window(szTitle, &szMainClass, args);
    wnd->CreateDefaultWindow(NULL, MainCallback);
    editWnd = new Window(L"Edit", &szEditClass, args);

    wnd->CreateDefaultWindow(NULL, MainCallback);
    wnd->SetBackgroundColor(RGB(100, 100, 100));

    list = new ListBox(L"", *wnd, 5000, args.hInstance, NULL);
    list->Create(BORDER, { 10, 10 }, { 500, 500 });

    list->AddElement(L"ONE");

    mainMenu = new Menu(L"Main", false, 500);

    mainMenu->AddSubMenu(
        {
            {L"Открыть", MF_STRING },
            {L"Сохранить", MF_STRING },
            {L"", MF_SEPARATOR },
            {L"Выход", MF_STRING }
        },
        1000,
        L"Файл"
    );
    mainMenu->AddSubMenu(
        {
            {L"По производителю 🠕", MF_STRING },
            {L"По производителю 🠗", MF_STRING },
            {L"По частоте 🠕", MF_STRING },
            {L"По частоте 🠗", MF_STRING }
        },
        2000,
        L"Сортировка"
    );

    mainMenu->Register(*wnd);

    listContext = new Menu(L"List context menu", true, 0);

    listContext->AddItems(
        {
            {L"Добавить", MF_STRING},
            {L"Изменить", MF_STRING},
            {L"Удалить", MF_STRING},
        },
        3000
    );

    return 0;
}

static int MainCallback(CallbackArgs args)
{
    if (Closing(args))
        Quit();

    if (list->IsContextMenu(args))
    {
        auto val = listContext->Track(list->Get(), args);

        if (val == listContext->GetIDByMenuIndex(0, 0))
        {
            wnd->Disable();
            editWnd->CreateDefaultWindow(*wnd, EditCallback);
        }

        if (val == listContext->GetIDByMenuIndex(1, 0))
            MessageBox(wnd->Get(), L"Option B", L"Notify", MB_OK);

        if (val == listContext->GetIDByMenuIndex(2, 0))
            MessageBox(wnd->Get(), L"Option C", L"Notify", MB_OK);

        return 0;
    }

    if (mainMenu->IsClicked(args, 0, 3))
        Quit();

    return 1;
}

static int EditCallback(CallbackArgs args)
{
    if (Closing(args))
    {
        wnd->Enable();
        DestroyWindow(*editWnd);
    }
    
    return 1;
}