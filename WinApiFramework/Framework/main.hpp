#pragma once
#include "libs.hpp"

wstring szMainClass = L"MainClass";
wstring szTitle = L"Title";

Window* wnd;
GLContext* context;

Mesh* kek, *monk;
GameObject* shrek, *monkey;

int Angle;
float zPos;

int MainCallback(CallbackArgs);
void Update();
void MainRenderer();

int _main_(MainArgs args)
{
    shrek = new GameObject();
    monkey = new GameObject();

    kek = new Mesh();
    monk = new Mesh();

    wnd = new Window(szTitle, &szMainClass, args);
    wnd->CreateCustomWindow(0, GL_WINDOW, { 10, 10 }, { 800, 600 }, NULL, NULL, NULL, MainCallback);

    context = new GLContext(wnd, 0, 16, 16, MainRenderer);
    context->AddSmooth();
    context->AddAmbienLight({ 255, 255, 255, 255 });

    UpdateCallback.push_back(Update);

    kek->Load("Shrek.obj");
    monk->Load("monkey.obj");

    shrek->AssignMesh(kek);
    monkey->AssignMesh(monk);

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
    Angle+=1;
    //zPos -= 0.5;
}

void MainRenderer()
{
    context->ClearBuffers(0);

    //glTranslatef(0, -5, -20 + zPos);
    ////glRotatef(Angle, 0, 1, 0);
    //glScalef(0.25, 0.25, 0.25);

    shrek->Transform.X = 2;
    shrek->Transform.Z = -10;
    shrek->Transform.Y = -3;
    shrek->ScaleObject(0.1);
    shrek->Rotation.Y = (float)Angle;
    shrek->Draw();

    //kek->Translate({ 10, 0, 0 });
    //kek->Rotate(Angle, { 0, 1, 0 });
    //kek->Draw({ 0, 255, 0, 255 });

    monkey->Transform.X = 2;
    monkey->Transform.Z = -10;
    monkey->ScaleObject(1);
    monkey->Rotation.Y = (float)Angle;
    monkey->Draw();
    /*monk->Translate({ -20, 0, 0 });
    monk->Rotate(-Angle, { 0, 1, 0 });
    monk->Scale({ 10, 10, 10 });
    monk->Draw({ 0, 255, 0, 255 });*/

    if(context)
        SwapBuffers(context->HDC());
}
