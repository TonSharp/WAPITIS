#include "main.hpp"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR IpszCmdLine, int nCmdShow)
{
    _main_({ hInst, hPrevInst, IpszCmdLine, nCmdShow});

    Msg* message = new Msg();

    while (message->Get())
        message->Dispatch();

    return message->wParam();
}