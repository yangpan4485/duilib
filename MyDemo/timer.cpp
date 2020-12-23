#include "timer.h"

#include <iostream>
#include <string>

TimerControl::TimerControl()
{

}
TimerControl::~TimerControl()
{

}

void TimerControl::Init()
{
	SetProcessDPIAware();
	_hInstance = GetModuleHandle(0);
	DuiLib::CPaintManagerUI::SetInstance(_hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("resources"));
}
bool TimerControl::CreateDUIWindow()
{
	_ownerWnd = Create(NULL, _T("Timer"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	if (!_ownerWnd)
	{
		std::cout << "create dui window failed" << std::endl;
		return false;
	}
	return true;
}
void TimerControl::ShowWindow()
{
	ShowModal();
}

LPCTSTR TimerControl::GetWindowClassName() const
{
	return _T("DUITimerFrame");
}
void TimerControl::Notify(DuiLib::TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		OnClick(msg);
	}
	else if (msg.sType == _T("valuechanged"))
	{
		OnValueChange(msg);
	}
    if (msg.sType == _T("link"))
    {
        DuiLib::CTextUI* pText = (DuiLib::CTextUI*)msg.pSender;
        DuiLib::CDuiString* str = pText->GetLinkContent(0);
        // CSDN
        ShellExecute(NULL, "open", str->GetData(), NULL, NULL, SW_SHOWNORMAL);

    }
}
LRESULT TimerControl::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	switch (uMsg) {
	case WM_CREATE:
		lRes = OnCreate(uMsg, wParam, lParam);
		break;
	case WM_CLOSE:
		lRes = OnClose(uMsg, wParam, lParam);
		break;
	case WM_TIMER: 
		lRes = OnTimer(uMsg, wParam, lParam); 
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

LRESULT TimerControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	_paintManager.Init(m_hWnd);
	DuiLib::CDialogBuilder builder;
	DuiLib::CControlUI* pRoot = builder.Create(_T("timer.xml"), (UINT)0, NULL, &_paintManager);
	_paintManager.AttachDialog(pRoot);
	_paintManager.AddNotifier(this);

	return 0;
}
LRESULT TimerControl::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

void TimerControl::OnClick(DuiLib::TNotifyUI& msg)
{
	if (msg.pSender->GetName() == _T("timerBtn"))
	{
		HWND hwnd = _paintManager.GetPaintWindow();
		SetTimer(hwnd, 1, 500, NULL);
	}
}
LRESULT TimerControl::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int count = 1;
    std::cout << "count:" << count << std::endl;
    std::string image = "timer/head_" + std::to_string(count);
    image = image + ".png";
	auto timerContainer = (DuiLib::CContainerUI*)_paintManager.FindControl(_T("timerContainer"));
    timerContainer->SetBkImage(image.c_str());
    count++;
    if (count > 26) {
        count = 1;
    }
	return 0;
}
void TimerControl::OnValueChange(DuiLib::TNotifyUI& msg)
{

} 