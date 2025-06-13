#include "DemoApp.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    DemoApp demoApp(1280, 960);

    demoApp.Init();
    demoApp.Loop();
    demoApp.UnInit();

    return (int)1;
}
