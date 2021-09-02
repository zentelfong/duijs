#pragma once
#include "quickjs/qjs.h"
#include "Utils/WinImplBase.h"

namespace duijs {

using namespace DuiLib;

class JsWindow:public WindowImplBase {
public:
	JsWindow(qjs::Context* context, qjs::Value& this_obj);
	~JsWindow();

	void Mark(JS_MarkFunc* mark_func);

	qjs::Value js_this() { return this_; }
	qjs::Value js_manager() { return paint_manager_; }

protected:
	LPCTSTR GetWindowClassName(void) const override;
	void InitResource() override;
	void InitWindow() override;
	void OnFinalMessage(HWND hWnd) override;
	void Notify(TNotifyUI& msg) override;
	CDuiString GetSkinFile() override;

	CDuiString GetSkinType() override;
	LPCTSTR GetManagerName() override;

	CControlUI* CreateControl(LPCTSTR pstrClass) override;
	LPCTSTR QueryControlText(LPCTSTR lpstrId, LPCTSTR lpstrType) override;

	LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	LRESULT OnKeyUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;

	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;

#if defined(WIN32) && !defined(UNDER_CE)
	LRESULT OnMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
#endif

	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled) override;
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

private:
	qjs::Context* context_;
	qjs::Value this_;
	qjs::Value paint_manager_;
};


void RegisterWindow(qjs::Module* module);

}//namespace
