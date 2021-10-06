#include "main.hpp"
#include "UpdateCallbacks.hpp"

void CallRenderCallbacks()
{
    if (!UpdateCallback.empty())
        for (const auto call : UpdateCallback)
            call();
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR IpszCmdLine, int nCmdShow)
{
    _main_({ hInst, hPrevInst, IpszCmdLine, nCmdShow});

    MSG msg;

    while (true)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
                return TRUE;
        }

        Mouse::Update();
        CallRenderCallbacks();
    }
}