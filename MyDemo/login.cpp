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
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("resources"));
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

        auto option = dynamic_cast<DuiLib::COptionUI*>(_paintManager.FindControl(_T("radioTeacher")));
        std::cout << "radioTeacher:" << option->IsSelected() << std::endl;
        option = dynamic_cast<DuiLib::COptionUI*>(_paintManager.FindControl(_T("radioStudent")));
        std::cout << "radioStudent:" << option->IsSelected() << std::endl;

        auto checkBox = dynamic_cast<DuiLib::CCheckBoxUI*>(_paintManager.FindControl(_T("CheckBox1")));
        std::cout << "CheckBox1:" << checkBox->GetCheck() << std::endl;
        checkBox = dynamic_cast<DuiLib::CCheckBoxUI*>(_paintManager.FindControl(_T("CheckBox2")));
        std::cout << "CheckBox2:" << checkBox->GetCheck() << std::endl;

        auto combo = dynamic_cast<DuiLib::CComboUI*>(_paintManager.FindControl(_T("env_type")));
        std::cout << "env_type:" << combo->GetText() << std::endl;
        std::cout << "env_type:" << combo->GetCurSel() << std::endl;  // 第一个输出0
        
    }
    else if (msg.pSender->GetName() == _T("btnQuit"))
    {
        Close();
    }
    else if (msg.pSender->GetName() == _T("radioTeacher"))
    {
        std::cout << "radioTeacher selected" << std::endl;
    }
    else if (msg.pSender->GetName() == _T("radioStudent"))
    {
        std::cout << "radioStudent selected" << std::endl;
    }
    else if (msg.pSender->GetName() == _T("CheckBox1"))
    {
        std::cout << "CheckBox2 click" << std::endl;
        
    }
    else if (msg.pSender->GetName() == _T("CheckBox2"))
    {
        std::cout << "CheckBox2 click" << std::endl;
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