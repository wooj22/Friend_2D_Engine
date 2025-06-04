#include "DemoApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    GameApp gameApp(1920, 1080);

    gameApp.Init();
    gameApp.Loop();
    gameApp.UnInit();

    return (int)1;
}
