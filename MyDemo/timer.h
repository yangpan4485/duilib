#pragma once

#include "UIlib.h"

class TimerControl : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
public:
	TimerControl();
	~TimerControl();

	void Init();
	bool CreateDUIWindow();
	void ShowWindow();

	LPCTSTR GetWindowClassName() const override;
	void Notify(DuiLib::TNotifyUI& msg) override;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void OnClick(DuiLib::TNotifyUI& msg);
	void OnValueChange(DuiLib::TNotifyUI& msg);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE _hInstance;
	DuiLib::CPaintManagerUI _paintManager{};
	HWND _ownerWnd{};
};