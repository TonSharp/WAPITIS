#pragma once
#include "libs.hpp"

//Сюда добавляйте свои библиотеки:

wstring szMainClass = L"MainClass";
wstring szTitle = L"Title";

Window* wnd;

GLContext* context;

int MainCallback(CallbackArgs);

void Update();
void MainRenderer();

float Angle = 1;
float zPos = 0;

int _main_(MainArgs args)
{
    wnd = new Window(szTitle, &szMainClass, args);
    wnd->CreateCustomWindow(0, GL_WINDOW, { 10, 10 }, { 800, 600 }, NULL, NULL, NULL, MainCallback);

    context = new GLContext(wnd, 0, 16, 16, MainRenderer);

    UpdateCallback.push_back(Update);

    return 0;
}

int MainCallback(CallbackArgs args)
{
    if (Closing(args))
    {
        context->Destroy();
        Quit();
    }

    float width, height;
    if (wnd->IsResize(&width, &height, args))
        context->ResizeScene(width, height);

    if (wnd->IsKeyDown(args, VK_LEFT))
        zPos -= 0.05;
    if (wnd->IsKeyDown(args, VK_RIGHT))
        zPos += 0.05;


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
    glRotatef(Angle, 1, 1, 1);

    DrawPolygon(
        {
            {-0.9, -1, 0},
            {-0.9, 0, 0},
            {0.9, 0, 0},
            {0.9, -1, 0}
        }, 
        { 100, 100, 100, 255 }
    );

    DrawPolygon(
        {
            {-1, 0, 0},
            {0, 1, 0},
            {1, 0, 0}
        },
        { 0, 255, 100, 255 }
    );

    DrawPolygon(
        {
            {-0.3, -0.6, 0.001},
            {-0.3, -0.1, 0.001},
            {0.3, -0.1, 0.001},
            {0.3, -0.6, 0.001}
        },
        { 255, 255, 0, 255 }
    );

    if(context != NULL)
        SwapBuffers(context->HDC());
}