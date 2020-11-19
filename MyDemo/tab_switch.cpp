#include "tab_switch.h"

#include <iostream>
#include <string>

TabSwitch::TabSwitch()
{

}
TabSwitch::~TabSwitch()
{

}

void TabSwitch::Init()
{
    SetProcessDPIAware();
    _hInstance = GetModuleHandle(0);
    DuiLib::CPaintManagerUI::SetInstance(_hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("..\\..\\..\\resources"));
}
bool TabSwitch::CreateDUIWindow()
{
    _ownerWnd = Create(NULL, _T("TabSwitch"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    if (!_ownerWnd)
    {
        std::cout << "create dui window failed" << std::endl;
        return false;
    }
    return true;
}
void TabSwitch::ShowWindow()
{
    ShowModal();
}

LPCTSTR TabSwitch::GetWindowClassName() const
{
    return _T("DUITabSwitchFrame");
}
void TabSwitch::Notify(DuiLib::TNotifyUI& msg)
{
    if (msg.sType == _T("click"))
    {
        OnClick(msg);
    }
    else if (msg.sType == _T("textchanged"))
    {
        OnEditTextChange(msg);
    }
    else if (msg.sType == _T("selectchanged"))
    {
        OnTableSelectChange(msg);
    }
}
void TabSwitch::OnClick(DuiLib::TNotifyUI& msg)
{
    
}
void TabSwitch::OnEditTextChange(DuiLib::TNotifyUI& msg)
{
    
}
void TabSwitch::OnTableSelectChange(DuiLib::TNotifyUI& msg)
{
    DuiLib::CDuiString name = msg.pSender->GetName();
    DuiLib::CTabLayoutUI* pTabSwitch = static_cast<DuiLib::CTabLayoutUI*>(_paintManager.FindControl(_T("tabSwitch")));
    if (!pTabSwitch)
    {
        return;
    }
    if (name.CompareNoCase(_T("basicTab")) == 0)
    {
        pTabSwitch->SelectItem(0);
    }
    if (name.CompareNoCase(_T("videoTab")) == 0)
    {
        pTabSwitch->SelectItem(1);
    }
    if (name.CompareNoCase(_T("audioTab")) == 0)
    {
        pTabSwitch->SelectItem(2);
    }
    if (name.CompareNoCase(_T("screenTab")) == 0)
    {
        pTabSwitch->SelectItem(3);
    }
    if (name.CompareNoCase(_T("accountTab")) == 0)
    {
        pTabSwitch->SelectItem(4);
    }
}
LRESULT TabSwitch::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT TabSwitch::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    _paintManager.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("tableSwitch.xml"), (UINT)0, NULL, &_paintManager);
    _paintManager.AttachDialog(pRoot);
    _paintManager.AddNotifier(this);
    return 0;
}
LRESULT TabSwitch::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}