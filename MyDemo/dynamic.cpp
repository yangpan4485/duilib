#include "dynamic.h"

#include <iostream>

DynamicControl::DynamicControl()
{

}
DynamicControl::~DynamicControl()
{

}

void DynamicControl::Init()
{
    SetProcessDPIAware();
    _hInstance = GetModuleHandle(0);
    DuiLib::CPaintManagerUI::SetInstance(_hInstance);
    DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + +_T("resources"));
}
bool DynamicControl::CreateDUIWindow()
{
    _ownerWnd = Create(NULL, _T("Dynamic"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    if (!_ownerWnd)
    {
        std::cout << "create dui window failed" << std::endl;
        return false;
    }
    return true;
}
void DynamicControl::ShowWindow()
{
    ShowModal();
}

LPCTSTR DynamicControl::GetWindowClassName() const
{
    return _T("DUIDynamicFrame");
}
void DynamicControl::Notify(DuiLib::TNotifyUI& msg)
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
LRESULT DynamicControl::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT DynamicControl::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    _paintManager.Init(m_hWnd);
    DuiLib::CDialogBuilder builder;
    DuiLib::CControlUI* pRoot = builder.Create(_T("dynamic.xml"), (UINT)0, NULL, &_paintManager);
    _paintManager.AttachDialog(pRoot);
    _paintManager.AddNotifier(this);
    InitWindow();

    return 0;
}
LRESULT DynamicControl::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

void DynamicControl::OnClick(DuiLib::TNotifyUI& msg)
{

}
void DynamicControl::OnValueChange(DuiLib::TNotifyUI& msg)
{

}

void DynamicControl::InitWindow()
{
    auto mainVertical = (DuiLib::CVerticalLayoutUI*)_paintManager.FindControl(_T("mainVertical"));
    DuiLib::CLabelUI* userIdLabel = new DuiLib::CLabelUI;
    userIdLabel->SetFloat(true);
    userIdLabel->SetText("用户名: ");
    // userIdLabel->SetPos({ 300,80,370,120 });
    SIZE leftTop = { 300,80 };
    userIdLabel->SetFixedXY(leftTop);
    userIdLabel->SetFixedWidth(70);
    userIdLabel->SetFixedHeight(30);
    userIdLabel->SetFont(0);
    mainVertical->Add(userIdLabel);
    
    DuiLib::CLabelUI* passwordLabel = new DuiLib::CLabelUI;
    passwordLabel->SetFloat(true);
    passwordLabel->SetText("密  码: ");
    leftTop = { 300,140 };
    passwordLabel->SetFixedXY(leftTop);
    passwordLabel->SetFixedWidth(70);
    passwordLabel->SetFixedHeight(30);
    passwordLabel->SetFont(0);
    mainVertical->Add(passwordLabel);

    DuiLib::CEditUI* userIdEdit = new DuiLib::CEditUI;
    userIdEdit->SetFloat(true);
    userIdEdit->SetName("passwordEdit");
    userIdEdit->SetText("");
    leftTop = { 370,85 };
    userIdEdit->SetFixedXY(leftTop);
    userIdEdit->SetFixedWidth(250);
    userIdEdit->SetFixedHeight(30);
    userIdEdit->SetFont(0);
    userIdEdit->SetBkColor(0xFFFFFFFF);
    userIdEdit->SetTextPadding({4,3,4,3});
    userIdEdit->SetTextColor(0xFF000000);
    userIdEdit->SetDisabledTextColor(0xFFA7A6AA);
    mainVertical->Add(userIdEdit);

    DuiLib::CEditUI* passwordEdit = new DuiLib::CEditUI;
    passwordEdit->SetFloat(true);
    passwordEdit->SetName("passwordEdit");
    passwordEdit->SetText("");
    leftTop = { 370,146 };
    passwordEdit->SetFixedXY(leftTop);
    passwordEdit->SetFixedWidth(250);
    passwordEdit->SetFixedHeight(30);
    passwordEdit->SetFont(0);
    passwordEdit->SetBkColor(0xFFFFFFFF);
    passwordEdit->SetTextPadding({ 4,3,4,3 });
    passwordEdit->SetTextColor(0xFF000000);
    passwordEdit->SetDisabledTextColor(0xFFA7A6AA);
    passwordEdit->SetPasswordMode(true);
    // passwordEdit->SetPasswordChar('.');
    mainVertical->Add(passwordEdit);

    DuiLib::CLabelUI* serverLabel = new DuiLib::CLabelUI;
    serverLabel->SetFloat(true);
    serverLabel->SetText("服务器: ");
    leftTop = { 300,200 };
    serverLabel->SetFixedXY(leftTop);
    serverLabel->SetFixedWidth(70);
    serverLabel->SetFixedHeight(30);
    serverLabel->SetFont(0);
    mainVertical->Add(serverLabel);

    DuiLib::CComboUI* envType = new DuiLib::CComboUI;
    envType->SetFloat(true);
    leftTop = { 375,200 };
    envType->SetFixedXY(leftTop);
    envType->SetFixedWidth(250);
    envType->SetFixedHeight(30);
    envType->SetItemTextColor(0xFF000000);
    envType->SetItemFont(2);
    envType->SetNormalImage("common/normal.png");
    envType->SetPushedImage("common/normal.png");
    envType->SetHotImage("common/normal.png");

    DuiLib::CListLabelElementUI* env1 = new DuiLib::CListLabelElementUI;
    env1->SetText(" 线上环境");
    env1->SetFixedHeight(30);
    envType->Add(env1);
    env1->Select(true);
    env1->SetVisible(true);
    env1->SetInternVisible(true);

    DuiLib::CListLabelElementUI* env2 = new DuiLib::CListLabelElementUI;
    env2->SetText(" 测试环境");
    env2->SetFixedHeight(30);
    envType->Add(env2);
    env2->SetVisible(true);
    env2->SetInternVisible(true);

    mainVertical->Add(envType);


    DuiLib::COptionUI* radioTeacher = new DuiLib::COptionUI;
    radioTeacher->SetFloat(true);
    radioTeacher->SetName("radioTeacher");
    radioTeacher->SetText("老师");
    radioTeacher->SetGroup("radio");
    leftTop = { 370,260 };
    radioTeacher->SetFixedXY(leftTop);
    radioTeacher->SetFixedWidth(80);
    radioTeacher->SetFixedHeight(30);
    radioTeacher->SetFont(0);
    radioTeacher->SetTextColor(0xFFbac0c5);
    radioTeacher->SetHotTextColor(0xFF386382);
    radioTeacher->SetSelectedTextColor(0xFF386382);
    radioTeacher->SetDisabledTextColor(0xFFbac0c5);
    radioTeacher->SetTextPadding({ 18,2,0,0 });
    // radioTeacher->SetSelectedImage("common/RadioBtnSel.png");
    // radioTeacher->SetNormalImage("common/RadioBtnNon.png");
    radioTeacher->SetAttribute(_T("selectedimage"), _T("file='common/RadioBtnSel.png' source='0,0,13,13' dest='0,9,14,23'"));
    radioTeacher->SetAttribute(_T("normalimage"), _T("file='common/RadioBtnNon.png' source='0,0,13,13' dest='0,9,14,23'"));

    mainVertical->Add(radioTeacher);

    DuiLib::COptionUI* radioStudent = new DuiLib::COptionUI;
    radioStudent->SetFloat(true);
    radioStudent->SetName("radioStudent");
    radioStudent->SetText("学生");
    radioStudent->SetGroup("radio");
    leftTop = { 500,260 };
    radioStudent->SetFixedXY(leftTop);
    radioStudent->SetFixedWidth(80);
    radioStudent->SetFixedHeight(30);
    radioStudent->SetFont(0);
    radioStudent->SetTextColor(0xFFbac0c5);
    radioStudent->SetHotTextColor(0xFF386382);
    radioStudent->SetSelectedTextColor(0xFF386382);
    radioStudent->SetDisabledTextColor(0xFFbac0c5);
    radioStudent->SetTextPadding({ 18,2,0,0 });
    radioStudent->SetAttribute(_T("selectedimage"), _T("file='common/RadioBtnSel.png' source='0,0,13,13' dest='0,9,14,23'"));
    radioStudent->SetAttribute(_T("normalimage"), _T("file='common/RadioBtnNon.png' source='0,0,13,13' dest='0,9,14,23'"));
    mainVertical->Add(radioStudent);

    DuiLib::CCheckBoxUI* CheckBox1 = new DuiLib::CCheckBoxUI;
    CheckBox1->SetFloat(true);
    CheckBox1->SetName(_T("CheckBox1"));
    CheckBox1->SetText(_T("选择1"));
    CheckBox1->SetToolTip(_T("选择1"));
    leftTop = { 370,320 };
    CheckBox1->SetFixedXY(leftTop);
    CheckBox1->SetFixedWidth(80);
    CheckBox1->SetFixedHeight(30);
    CheckBox1->SetFont(0);
    CheckBox1->SetTextColor(0xFFbac0c5);
    CheckBox1->SetHotTextColor(0xFF386382);
    CheckBox1->SetSelectedTextColor(0xFF386382);
    CheckBox1->SetDisabledTextColor(0xFFbac0c5);
    CheckBox1->SetTextPadding({ 20,2,0,0 });
    // CheckBox1->SetSelectedImage("common/checked.png");
    // CheckBox1->SetNormalImage("common/unchecked.png");
    CheckBox1->SetAttribute(_T("selectedimage"), _T("file='common/checked.png' dest='0,8,16,24'"));
    CheckBox1->SetAttribute(_T("normalimage"), _T("file='common/unchecked.png' dest='0,8,16,24'"));
    mainVertical->Add(CheckBox1);

    DuiLib::CCheckBoxUI* CheckBox2 = new DuiLib::CCheckBoxUI;
    CheckBox2->SetFloat(true);
    CheckBox2->SetName(_T("CheckBox2"));
    CheckBox2->SetText(_T("选择2"));
    CheckBox2->SetToolTip(_T("选择2"));
    leftTop = { 500,320 };
    CheckBox2->SetFixedXY(leftTop);
    CheckBox2->SetFixedWidth(80);
    CheckBox2->SetFixedHeight(30);
    CheckBox2->SetFont(0);
    CheckBox2->SetTextColor(0xFFbac0c5);
    CheckBox2->SetHotTextColor(0xFF386382);
    CheckBox2->SetSelectedTextColor(0xFF386382);
    CheckBox2->SetDisabledTextColor(0xFFbac0c5);
    CheckBox2->SetTextPadding({ 20,2,0,0 });
    CheckBox2->SetAttribute(_T("selectedimage"), _T("file='common/checked.png' dest='0,8,16,24'"));
    CheckBox2->SetAttribute(_T("normalimage"), _T("file='common/unchecked.png' dest='0,8,16,24'"));
    mainVertical->Add(CheckBox2);

    DuiLib::CButtonUI* btnLogin = new DuiLib::CButtonUI;
    btnLogin->SetFloat(true);
    btnLogin->SetName(_T("btnLogin"));
    btnLogin->SetText(_T("登录"));
    btnLogin->SetToolTip(_T("登录"));
    btnLogin->SetAttribute("pos", "300,390,400,420");
    btnLogin->SetFont(0);
    btnLogin->SetNormalImage("common/button_normal.bmp");
    btnLogin->SetHotImage("common/button_over.bmp");
    btnLogin->SetPushedImage("common/button_down.bmp");
    mainVertical->Add(btnLogin);

    DuiLib::CButtonUI* btnQuit = new DuiLib::CButtonUI;
    btnQuit->SetFloat(true);
    btnQuit->SetName(_T("btnLogin"));
    btnQuit->SetText(_T("退出"));
    btnQuit->SetToolTip(_T("退出"));
    btnQuit->SetAttribute("pos", "500,390,600,420");
    btnQuit->SetFont(0);
    btnQuit->SetNormalImage("common/button_normal.bmp");
    btnQuit->SetHotImage("common/button_over.bmp");
    btnQuit->SetPushedImage("common/button_down.bmp");
    mainVertical->Add(btnQuit);
}