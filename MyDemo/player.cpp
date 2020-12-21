#include "player.h"

#include <iostream>
#include <chrono>

#include "d3d9_player.h"

#include "my_window.h"

PlayerWnd::PlayerWnd()
{
    std::string filename = "C:\\byte\\duilib\\resources\\480x272_yuv420p.yuv";
    _fin.open(filename, std::ios::in | std::ios::binary);
}
PlayerWnd::~PlayerWnd()
{
    std::cout << "~PlayerWnd()" << std::endl;
    _running = false;
    if (_work.joinable())
    {
        _work.join();
    }
    _fin.close();
}

void PlayerWnd::Init()
{
    SetProcessDPIAware();
    _hInstance = GetModuleHandle(0);
    DuiLib::CPaintManagerUI::SetInstance(_hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("..\\..\\..\\resources"));
}
bool PlayerWnd::CreateDUIWindow()
{
    _ownerWnd = Create(NULL, _T("Player"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    if (!_ownerWnd)
    {
        std::cout << "create dui window failed" << std::endl;
        return false;
    }
    return true;
}
void PlayerWnd::ShowWindow()
{
    ShowModal();
}

LPCTSTR PlayerWnd::GetWindowClassName() const
{
    return _T("DUIPlayerFrame");
}
void PlayerWnd::Notify(DuiLib::TNotifyUI& msg)
{
    if (msg.sType == _T("click"))
    {
        OnClick(msg);
    }
    else if (msg.sType == _T("valuechanged"))
    {
        OnValueChange(msg);
    }
}
LRESULT PlayerWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT lRes = 0;
    switch (uMsg) {
    case WM_CREATE:
        lRes = OnCreate(uMsg, wParam, lParam);
        break;
    case WM_CLOSE:
        lRes = OnClose(uMsg, wParam, lParam);
        break;
    default:
        break;
    }
    if (_paintManager.MessageHandler(uMsg, wParam, lParam, lRes))
    {
        return lRes;
    }

    return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT PlayerWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    _paintManager.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("player.xml"), (UINT)0, this, &_paintManager);
    _paintManager.AttachDialog(pRoot);
    _paintManager.AddNotifier(this);
    InitWindow();

    return 0;
}
LRESULT PlayerWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void PlayerWnd::OnClick(DuiLib::TNotifyUI& msg)
{
    if (msg.pSender->GetName() == "btnPlay") {
        _renderWnd = static_cast<CMyWindowUI*>(_paintManager.FindControl(_T("videoDisplay")));
        if (_running) {
            return;
        }
        _running = true;
        if (_work.joinable()) {
            _work.join();
        }
        std::thread work = std::thread([&]() {
            
            uint32_t width = 480;
            uint32_t height = 272;

            if (!_yuv_player)
            {
                _yuv_player = std::make_shared<D3D9Player>();
                _yuv_player->Init(width, height, I420);
                HWND hwnd = _renderWnd->GetHwnd();
                _renderWnd->SetPos({ 0,0,960,544 });
                ::ShowWindow(hwnd, true);
                _yuv_player->SetWindow(hwnd);

            }
            uint8_t* data = new uint8_t[width * height * 3 / 2];
            while (_running) {
                _fin.read((char*)data, width * height * 3 / 2);
                _yuv_player->Render(data);
                if (_fin.eof())
                {
                    _fin.clear();
                    _fin.seekg(0);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(40));
            }
            std::cout << "end" << std::endl;
            delete[] data;
        });
        work.detach();
    }
    else if (msg.pSender->GetName() == "btnPause")
    {
        _running = false;
    }
}
void PlayerWnd::OnValueChange(DuiLib::TNotifyUI& msg)
{

}

void PlayerWnd::InitWindow()
{

}

DuiLib::CControlUI* PlayerWnd::CreateControl(LPCTSTR pstrClass)
{
    if (_tcscmp(pstrClass, _T("MyWindow")) == 0) {
        CMyWindowUI* wndui = new CMyWindowUI();
        HWND wnd = CreateWindow(_T("STATIC"), _T(""),
            WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
            0, 0, 0, 0, _paintManager.GetPaintWindow(), (HMENU)0, NULL, NULL);
        wndui->Attach(wnd);
        return wndui;
    }
    return NULL;
}