#include "main.hpp"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR IpszCmdLine, int nCmdShow)
{
    _main_({ hInst, hPrevInst, IpszCmdLine, nCmdShow, WndProc });

    Msg* message = new Msg();

    while (message->Get())
        message->Dispatch();

    return message->wParam();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            int ret = _callback_({ hwnd, msg, wParam, lParam });
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}