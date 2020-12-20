#pragma once
#include "UIlib.h"

class DynamicControl : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
public:
    DynamicControl();
    ~DynamicControl();

    void Init();
    bool CreateDUIWindow();
    void ShowWindow();

    LPCTSTR GetWindowClassName() const override;
    void Notify(DuiLib::TNotifyUI& msg) override;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);

    void OnClick(DuiLib::TNotifyUI& msg);
    void OnValueChange(DuiLib::TNotifyUI& msg);

    void InitWindow();

private:
    HINSTANCE _hInstance;
    DuiLib::CPaintManagerUI _paintManager{};
    HWND _ownerWnd{};
};