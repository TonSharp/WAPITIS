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
    wnd->CreateCustomWindow(0, GL_WINDOW, { 10, 10 }, { 800, 600 }, NULL, NULL, NULL, MainCallback);

    context = new GLContext(wnd, 0, 16, 16, MainRenderer);
    context->AddAmbienLight({ 255, 255, 255, 255 });
    glEnable(GL_LIGHT0);

    UpdateCallback.push_back(Update);

    return 0;
}

int MainCallback(CallbackArgs args)
{
    if (Closing(args))
    {
        Quit();
    }
    return 1;
}

void Update()
{
    context->Render();
    Angle++;
}

void MainRenderer()
{
    context->ClearBuffers(0);
    glLoadIdentity();

    glTranslatef(0, 0, zPos - 3.5);
    glRotatef(Angle, 0, 1, 0);

    DrawBox({ 0, 0, 0 }, 2, 1, 2, { 100, 100, 100, 255 });

    if(context != NULL)
        SwapBuffers(context->HDC());
}
