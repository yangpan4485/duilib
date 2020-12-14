#include <Windows.h>
#include <iostream>
#include "login.h"
#include "tab_switch.h"
#include "complex_control.h"
#include "timer.h"

int main(void) {
    TimerControl timerWindow;
	timerWindow.Init();
	timerWindow.CreateDUIWindow();
	timerWindow.ShowWindow();
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