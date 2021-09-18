#pragma once
#include "libs.hpp"

//Сюда добавляйте свои библиотеки:

wstring szMainClass = L"MainClass";
wstring szTitle = L"Title";

Window* wnd;

GLContext* context;

int MainCallback(CallbackArgs);
void MainRenderer();

float Angle = 1;

int _main_(MainArgs args)
{
    wnd = new Window(szTitle, &szMainClass, args);
    wnd->CreateCustomWindow(NULL, GL_WINDOW, { 10, 10 }, { 500, 500 }, NULL, NULL, NULL, MainCallback);

    context = new GLContext(wnd, NULL, 16, 16, MainRenderer);
    context->ClearColor(0, 0, 0, 255);

    return 0;
}

int MainCallback(CallbackArgs args)
{
    context->Render();

    if (Closing(args))
    {
        context->Destroy();
        Quit();
    }

    if (wnd->IsCreate(args))
    {
        context->Init();
    }

    /*if (wnd->IsDraw(args))
        context->Render();

    float width, height;
    if (wnd->IsResize(&width, &height, args))
        context->ResizeScene(width, height);*/


    return 1;
}

void MainRenderer()
{
    // Очищаем буфер цвета и глубины
    // чтобы старый (неповернутый) прямоугольник - стирался
    context->ClearBuffers(NULL);

    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, 0.0f);  // Вверх
    glVertex3f(-1.0f, -1.0f, 0.0f);  // Слева снизу
    glVertex3f(1.0f, -1.0f, 0.0f);  // Справа снизу
    glEnd();

    //glLoadIdentity();

    // Поворачиваем сцену на угол Angle, по осям X (1.0), Y (1.0), но не Z (0.0)
    //glRotatef(Angle, 1.0, 1.0, 0.0);

    //// Цвет прямоугольника - темно-зеленый:
    //// R = 0/255   = 0
    //// G = 127/255 = 0.5
    //// B = 0/255   = 0
    //glColor3f(0.0, 0.5, 0.0);

    //// Рисование прямоугольника
    //// высота: 1 половина высоты окна =                      1.0 ед.
    //// ширина: 0.25 ширины окна = 0.5 половины ширины окна = 0.5 ед.
    //glBegin(GL_POLYGON);
    //glVertex2f(0, 0); // Левый-нижний угол
    //glVertex2f(0, 1.0); // Левый-верхний угол
    //glVertex2f(1, 1.0); // Правый-верхний угол
    //glVertex2f(1, 0); // Правый-нижний угол
    //glEnd();

    if(context != NULL)
        SwapBuffers(context->HDC());
}