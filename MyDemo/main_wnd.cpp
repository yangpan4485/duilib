#include "main_wnd.h"

#include <iostream>
#include "child_wnd.h"
#include <thread>
#include <chrono>

MainWnd::MainWnd()
{

}
MainWnd::~MainWnd()
{
    std::cout << "~MainWnd()" << std::endl;
}

void MainWnd::Init()
{
    SetProcessDPIAware();
    _hInstance = GetModuleHandle(0);
    DuiLib::CPaintManagerUI::SetInstance(_hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("resources"));
}
bool MainWnd::CreateDUIWindow()
{
    _ownerWnd = Create(NULL, _T("Main"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    if (!_ownerWnd)
    {
        std::cout << "create dui window failed" << std::endl;
        return false;
    }
    return true;
}
void MainWnd::ShowWindow()
{
    ShowModal();
}

LPCTSTR MainWnd::GetWindowClassName() const
{
    return _T("DUIMainFrame");
}
void MainWnd::Notify(DuiLib::TNotifyUI& msg)
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
LRESULT MainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT MainWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    _paintManager.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("mainWnd.xml"), (UINT)0, NULL, &_paintManager);
    _paintManager.AttachDialog(pRoot);
    _paintManager.AddNotifier(this);
    InitWindow();

    return 0;
}
LRESULT MainWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    std::cout << "OnClose" << std::endl;
    _childWnd->Close();
    // _childWnd->CloseWindow();
    /*if (::IsWindow(_chdWnd)) {
        DestroyWindow(_chdWnd);
    }*/
    //if (_childWnd)
    //{
    //    std::cout << "Close Child Window" << std::endl;
    //    _childWnd->Close(0);
    //    // _childWnd = NULL;
    //}
    std::cout << "Closed" << std::endl;
    return 0;
}

void MainWnd::OnClick(DuiLib::TNotifyUI& msg)
{
    if (msg.pSender->GetName() == "btnLogin")
    {
        _childWnd = new ChildWnd();
        // �����һ������Ϊ NULL���Ӵ��ڵ����󻹿��Լ������������ڣ���ʵ���ʱ�����������ǲ��еģ���û�и��ӹ�ϵ
        // �����һ������Ϊ��ǰ���� HWND����ô����Ӵ��ڵĸ����ھ��ǵ�ǰ���ڣ�_ownerWnd��
        // �����Ӵ���û�йرյ�ʱ����û�а취���������ڵ�
        // ::EnableWindow(m_hwnd , false); �ô�����Ч��
        _chdWnd = _childWnd->Create(NULL, _T("Child"), UI_WNDSTYLE_DIALOG, 0);
        // ����һ�� dialog ����
        // _childWnd->Create(_ownerWnd, _T("Child"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
        // _childWnd->CenterWindow();
        // _childWnd->ShowModal();
        _childWnd->CenterWindow();
        _childWnd->ShowWindow(true, false);
        _childWnd->ShowModal();
        // SetWindowPos(_ownerWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        // SetWindowPos(_chdWnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else if (msg.pSender->GetName() == "btnQuit")
    {
        // SetWindowPos(_ownerWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        /*_childWnd->Close();
        _childWnd = NULL;*/
        Close();
    }
}
void MainWnd::OnValueChange(DuiLib::TNotifyUI& msg)
{

}

void MainWnd::InitWindow()
{

}