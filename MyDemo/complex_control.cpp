#include "complex_control.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

ComplexControl::ComplexControl()
{

}

ComplexControl::~ComplexControl()
{

}

void ComplexControl::Init()
{
    SetProcessDPIAware();
    _hInstance = GetModuleHandle(0);
    DuiLib::CPaintManagerUI::SetInstance(_hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("..\\..\\..\\resources"));
}
bool ComplexControl::CreateDUIWindow()
{
    _ownerWnd = Create(NULL, _T("Complex"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    if (!_ownerWnd)
    {
        std::cout << "create dui window failed" << std::endl;
        return false;
    }
    return true;
}
void ComplexControl::ShowWindow()
{
    ShowModal();
}

LPCTSTR ComplexControl::GetWindowClassName() const
{
    return _T("DUICOMPLEXFrame");
}
void ComplexControl::Notify(DuiLib::TNotifyUI& msg)
{
    if (msg.sType == _T("click"))
    {
        OnClick(msg);
    }
}
LRESULT ComplexControl::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT ComplexControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    _paintManager.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("complexControl.xml"), (UINT)0, NULL, &_paintManager);
    _paintManager.AttachDialog(pRoot);
    _paintManager.AddNotifier(this);
    InitWindow();

    return 0;
}

LRESULT ComplexControl::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void ComplexControl::OnClick(DuiLib::TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("startBtn"))
    {
        DuiLib::CProgressUI* pProgress = static_cast<DuiLib::CProgressUI*>(_paintManager.FindControl(_T("progressControl")));
        std::thread work = std::thread([pProgress, this]() {
            for (int i = 1; i <= 100; ++i) {
                pProgress->SetValue(i);
                std::string text = std::to_string(i) + "%";
                pProgress->SetText(text.c_str());
                Sleep(50);
            }
        });
        work.detach();
    }
}

void ComplexControl::InitWindow()
{
#if 0
    DuiLib::CActiveXUI* pActiveXUI = static_cast<DuiLib::CActiveXUI*>(_paintManager.FindControl(_T("ActiveXDemo1")));
    if (pActiveXUI)
    {
        IWebBrowser2* pWebBrowser = NULL;

        pActiveXUI->SetDelayCreate(false);              // �൱�ڽ�����������DelayCreate���Ը�ΪFALSE����duilib�Դ���FlashDemo����Կ���������ΪTRUE             
        pActiveXUI->CreateControl(CLSID_WebBrowser);    // �൱�ڽ�����������Clsid����������{8856F961-340A-11D0-A96B-00C04FD705A2}��������CLSID_WebBrowser������뿴��Ӧ��ֵ�����<ExDisp.h>
        pActiveXUI->GetControl(IID_IWebBrowser2, (void**)&pWebBrowser);

        if (pWebBrowser != NULL)
        {
            pWebBrowser->Navigate(L"https://www.baidu.com/", NULL, NULL, NULL, NULL);
            pWebBrowser->Release();
        }
    }
#endif
}