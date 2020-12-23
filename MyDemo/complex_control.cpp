#include "complex_control.h"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

using namespace DuiLib;

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
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("resources"));
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
    else if (msg.sType == _T("valuechanged"))
    {
        OnValueChange(msg);
    }
	else if (msg.sType == _T("itemclick"))
	{
		OnItemClick(msg);
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
    if (msg.pSender->GetName() == _T("okBtn"))
    {
        // 如果有手动输入的换行，字符会被覆盖掉
        DuiLib::CRichEditUI* pRichEdit = static_cast<DuiLib::CRichEditUI*>(_paintManager.FindControl(_T("wordedit")));
        std::cout << pRichEdit->GetText() << std::endl;
    }
}

void ComplexControl::OnValueChange(DuiLib::TNotifyUI& msg)
{
    if (msg.pSender->GetName() == _T("sliderControl"))
    {
        DuiLib::CSliderUI* slider = static_cast<DuiLib::CSliderUI*>(_paintManager.FindControl(_T("sliderControl")));
        // 获取 slider 的进度
        std::cout << "slider:" << slider->GetValue() << std::endl;
    }
}

void ComplexControl::OnItemClick(DuiLib::TNotifyUI& msg)
{
	auto name = msg.pSender->GetName();
	DuiLib::CTreeNodeUI* treeNode = nullptr;
	if (name == "nodePlaylist")
	{
		treeNode = static_cast<DuiLib::CTreeNodeUI*>(_paintManager.FindControl(_T("nodePlaylist")));
	}
	else if (name == "onlineMedialist")
	{
		treeNode = static_cast<DuiLib::CTreeNodeUI*>(_paintManager.FindControl(_T("onlineMedialist")));
	}
	else if (name == "gameCenterlist")
	{
		treeNode = static_cast<DuiLib::CTreeNodeUI*>(_paintManager.FindControl(_T("gameCenterlist")));
	}

	if (treeNode && treeNode->IsHasChild()) {
		CTreeViewUI	* pTreeView = treeNode->GetTreeView();
		if (NULL != pTreeView) {
			CCheckBoxUI* pFolder = treeNode->GetFolderButton();
			pFolder->Selected(!pFolder->IsSelected());
			treeNode->SetVisibleTag(!pFolder->GetCheck());
			pTreeView->SetItemExpand(!pFolder->GetCheck(), treeNode);
		}
	}
}

void ComplexControl::InitWindow()
{
    CListUI* pList = static_cast<CListUI*>(_paintManager.FindControl(_T("listControl")));
    for (int i = 0; i < 20; i++)
    {
        CListTextElementUI* pItem = new CListTextElementUI();
        pItem->SetTag(i);
        pItem->SetFixedHeight(30);
        pList->Add(pItem);
        std::string number;
        if (i < 10)
        {
            number = "100" + std::to_string(i);
        }
        else {
            number = "10" + std::to_string(i);
        }
        std::string score = std::to_string(i + 60);
        pItem->SetText(0, _T("张三"));
        pItem->SetText(1, _T(number.c_str()));
        pItem->SetText(2, _T(score.c_str()));
    }
#if 0
    DuiLib::CActiveXUI* pActiveXUI = static_cast<DuiLib::CActiveXUI*>(_paintManager.FindControl(_T("ActiveXDemo1")));
    if (pActiveXUI)
    {
        IWebBrowser2* pWebBrowser = NULL;

        pActiveXUI->SetDelayCreate(false);              // 相当于界面设计器里的DelayCreate属性改为FALSE，在duilib自带的FlashDemo里可以看到此属性为TRUE             
        pActiveXUI->CreateControl(CLSID_WebBrowser);    // 相当于界面设计器里的Clsid属性里填入{8856F961-340A-11D0-A96B-00C04FD705A2}，建议用CLSID_WebBrowser，如果想看相应的值，请见<ExDisp.h>
        pActiveXUI->GetControl(IID_IWebBrowser2, (void**)&pWebBrowser);

        if (pWebBrowser != NULL)
        {
            pWebBrowser->Navigate(L"https://www.baidu.com/", NULL, NULL, NULL, NULL);
            pWebBrowser->Release();
        }
    }
#endif
}