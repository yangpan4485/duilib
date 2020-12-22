#include <Windows.h>
#include <iostream>
#include "login.h"
#include "tab_switch.h"
#include "complex_control.h"
#include "timer.h"
#include "dynamic.h"
#include "main_wnd.h"
#include "player.h"

// #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

int main(void) {
    PlayerWnd* playerWindow = new PlayerWnd;
    playerWindow->Init();
    playerWindow->CreateDUIWindow();
    playerWindow->ShowWindow();
	getchar();
#if 0
    DynamicControl dynamicWindow;
    dynamicWindow.Init();
    dynamicWindow.CreateDUIWindow();
    dynamicWindow.ShowWindow();
#endif
#if 0
    TimerControl timerWindow;
	timerWindow.Init();
	timerWindow.CreateDUIWindow();
	timerWindow.ShowWindow();
#endif
#if 0
    ComplexControl complexWindow;
    complexWindow.Init();
    complexWindow.CreateDUIWindow();
    complexWindow.ShowWindow();
#endif
#if 0
    TabSwitch tabSwitch;
    tabSwitch.Init();
    tabSwitch.CreateDUIWindow();
    tabSwitch.ShowWindow();
#endif
#if 0
    Login loginWindow;
    loginWindow.Init();
    loginWindow.CreateDUIWindow();
    loginWindow.ShowWindow();
#endif
    return 0;
}