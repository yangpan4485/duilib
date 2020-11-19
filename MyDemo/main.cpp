#include <Windows.h>
#include <iostream>
#include "login.h"
#include "tab_switch.h"

int main(void) {
    TabSwitch tabSwitch;
    tabSwitch.Init();
    tabSwitch.CreateDUIWindow();
    tabSwitch.ShowWindow();
#if 0
    Login loginWindow;
    loginWindow.Init();
    loginWindow.CreateDUIWindow();
    loginWindow.ShowWindow();
#endif
    return 0;
}