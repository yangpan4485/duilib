#include "login.h"

#include <iostream>
#include <string>

Login::Login()
{

}
Login::~Login()
{

}

void Login::Init()
{
    SetProcessDPIAware();
    _hInstance = GetModuleHandle(0);
    DuiLib::CPaintManagerUI::SetInstance(_hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("..\\..\\..\\resources"));
}
bool Login::CreateDUIWindow()
{
    _ownerWnd = Create(NULL, _T("Login"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    if (!_ownerWnd)
    {
        std::cout << "create dui window failed" << std::endl;
        return false;
    }
    return true;
}
void Login::ShowWindow()
{
    ShowModal();
}

LPCTSTR Login::GetWindowClassName() const
{
    return _T("DUILOGINFrame");
}
void Login::Notify(DuiLib::TNotifyUI& msg)
{
    if (msg.sType == _T("click"))
    {
        OnClick(msg);
    }
    else if (msg.sType == _T("textchanged"))
    {
        OnEditTextChange(msg);
    }
}
void Login::OnClick(DuiLib::TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("btnLogin")) 
    {
        auto editUserId = (DuiLib::CEditUI*)_paintManager.FindControl(_T("userIdEdit"));
        auto editPassword = (DuiLib::CEditUI*)_paintManager.FindControl(_T("passwordEdit"));
        std::string userId = editUserId->GetText();
        std::string password = editPassword->GetText();
        std::cout << "userId:" << userId << std::endl;
        std::cout << "password:" << password << std::endl;
    }
    else if (msg.pSender->GetName() == _T("btnQuit"))
    {
        Close();
    }
}
void Login::OnEditTextChange(DuiLib::TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("passwordEdit")) {
        
    }
}
LRESULT Login::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) 
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

LRESULT Login::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    _paintManager.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("login.xml"), (UINT)0, NULL, &_paintManager);
    _paintManager.AttachDialog(pRoot);
    _paintManager.AddNotifier(this);
    return 0;
}
LRESULT Login::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}