#include "child_wnd.h"

#include <iostream>

ChildWnd::ChildWnd()
{

}
ChildWnd::~ChildWnd()
{

}

LPCTSTR ChildWnd::GetWindowClassName() const
{
    return _T("DUIChildFrame");
}
void ChildWnd::Notify(DuiLib::TNotifyUI& msg)
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
LRESULT ChildWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // std::cout << "uMsg:" << uMsg << std::endl;
    LRESULT lRes = 0;
    switch (uMsg) {
    case WM_CREATE:
        lRes = OnCreate(uMsg, wParam, lParam);
        break;
    case WM_CLOSE:
        std::cout << "Child On Close" << std::endl;
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

LRESULT ChildWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    _paintManager.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("childWnd.xml"), (UINT)0, NULL, &_paintManager);
    _paintManager.AttachDialog(pRoot);
    _paintManager.AddNotifier(this);
    InitWindow();

    return 0;
}
LRESULT ChildWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void ChildWnd::OnClick(DuiLib::TNotifyUI& msg)
{
    if (msg.pSender->GetName() == "btnLogin")
    {
        
    }
    else if (msg.pSender->GetName() == "btnQuit")
    {
        Close();
    }
}
void ChildWnd::OnValueChange(DuiLib::TNotifyUI& msg)
{

}

void ChildWnd::InitWindow()
{

}

void ChildWnd::CloseWindow()
{
    std::cout << "Close Window" << std::endl;
    Close();
}