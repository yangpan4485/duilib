#include <Windows.h>
#include <iostream>
#include "login.h"
#include "tab_switch.h"
#include "complex_control.h"

int main(void) {
    ComplexControl complexWindow;
    complexWindow.Init();
    complexWindow.CreateDUIWindow();
    complexWindow.ShowWindow();
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