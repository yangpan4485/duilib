#pragma once

#include "UIlib.h"

#include <thread>
#include <fstream>

#include "my_window.h"

class D3D9Player;

class PlayerWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI, public DuiLib::IDialogBuilderCallback
{
public:
    PlayerWnd();
    ~PlayerWnd();

    void Init();
    bool CreateDUIWindow();
    void ShowWindow();

    LPCTSTR GetWindowClassName() const override;
    void Notify(DuiLib::TNotifyUI& msg) override;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
    DuiLib::CControlUI* CreateControl(LPCTSTR pstrClass) override;

    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
    LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);

    void OnClick(DuiLib::TNotifyUI& msg);
    void OnValueChange(DuiLib::TNotifyUI& msg);

    void InitWindow();

private:
    HINSTANCE _hInstance;
    HICON _hIcon{};
    DuiLib::CPaintManagerUI _paintManager{};
    HWND _ownerWnd{};

    bool _running{ false };
    std::thread _work{};
    std::ifstream _fin{};
    std::shared_ptr<D3D9Player> _yuv_player{};

    CMyWindowUI* _renderWnd{};
    std::string _filename{};
};