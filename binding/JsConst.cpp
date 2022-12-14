#include "Util.h"

namespace duijs {

void RegisterConst(qjs::Module* module) {

	EXPORT_CONST_VALUE(WS_OVERLAPPED);
	EXPORT_CONST_VALUE(WS_POPUP);
	EXPORT_CONST_VALUE(WS_CHILD);
	EXPORT_CONST_VALUE(WS_MINIMIZE);
	EXPORT_CONST_VALUE(WS_VISIBLE);
	EXPORT_CONST_VALUE(WS_DISABLED);
	EXPORT_CONST_VALUE(WS_CLIPSIBLINGS);
	EXPORT_CONST_VALUE(WS_CLIPCHILDREN);
	EXPORT_CONST_VALUE(WS_MAXIMIZE);
	EXPORT_CONST_VALUE(WS_CAPTION);
	EXPORT_CONST_VALUE(WS_BORDER);
	EXPORT_CONST_VALUE(WS_DLGFRAME);
	EXPORT_CONST_VALUE(WS_VSCROLL);
	EXPORT_CONST_VALUE(WS_HSCROLL);
	EXPORT_CONST_VALUE(WS_SYSMENU);
	EXPORT_CONST_VALUE(WS_THICKFRAME);
	EXPORT_CONST_VALUE(WS_GROUP);
	EXPORT_CONST_VALUE(WS_TABSTOP);
	EXPORT_CONST_VALUE(WS_MINIMIZEBOX);

	EXPORT_CONST_VALUE(WS_MAXIMIZEBOX);
	EXPORT_CONST_VALUE(WS_TILED);
	EXPORT_CONST_VALUE(WS_ICONIC);
	EXPORT_CONST_VALUE(WS_SIZEBOX);
	EXPORT_CONST_VALUE(WS_TILEDWINDOW);
	EXPORT_CONST_VALUE(WS_OVERLAPPEDWINDOW);
	EXPORT_CONST_VALUE(WS_POPUPWINDOW);
	EXPORT_CONST_VALUE(WS_CHILDWINDOW);


	EXPORT_CONST_VALUE(WS_EX_DLGMODALFRAME);
	EXPORT_CONST_VALUE(WS_EX_NOPARENTNOTIFY);
	EXPORT_CONST_VALUE(WS_EX_TOPMOST);
	EXPORT_CONST_VALUE(WS_EX_ACCEPTFILES);
	EXPORT_CONST_VALUE(WS_EX_TRANSPARENT);
	EXPORT_CONST_VALUE(WS_EX_MDICHILD);
	EXPORT_CONST_VALUE(WS_EX_TOOLWINDOW);
	EXPORT_CONST_VALUE(WS_EX_WINDOWEDGE);
	EXPORT_CONST_VALUE(WS_EX_CLIENTEDGE);
	EXPORT_CONST_VALUE(WS_EX_CONTEXTHELP);
	EXPORT_CONST_VALUE(WS_EX_RIGHT);
	EXPORT_CONST_VALUE(WS_EX_LEFT);
	EXPORT_CONST_VALUE(WS_EX_RTLREADING);
	EXPORT_CONST_VALUE(WS_EX_LTRREADING);
	EXPORT_CONST_VALUE(WS_EX_LEFTSCROLLBAR);
	EXPORT_CONST_VALUE(WS_EX_RIGHTSCROLLBAR);
	EXPORT_CONST_VALUE(WS_EX_CONTROLPARENT);
	EXPORT_CONST_VALUE(WS_EX_STATICEDGE);
	EXPORT_CONST_VALUE(WS_EX_APPWINDOW);
	EXPORT_CONST_VALUE(WS_EX_OVERLAPPEDWINDOW);

	EXPORT_CONST_VALUE(WS_EX_PALETTEWINDOW);
	EXPORT_CONST_VALUE(WS_EX_LAYERED);
	EXPORT_CONST_VALUE(WS_EX_NOINHERITLAYOUT);
	EXPORT_CONST_VALUE(WS_EX_LAYOUTRTL);
	EXPORT_CONST_VALUE(WS_EX_COMPOSITED);
	EXPORT_CONST_VALUE(WS_EX_NOACTIVATE);

	EXPORT_CONST_VALUE(MK_CONTROL);
	EXPORT_CONST_VALUE(MK_MBUTTON);
	EXPORT_CONST_VALUE(MK_RBUTTON);
	EXPORT_CONST_VALUE(MK_SHIFT);
	EXPORT_CONST_VALUE(MK_XBUTTON1);
	EXPORT_CONST_VALUE(MK_XBUTTON2);


	EXPORT_CONST_VALUE(DT_TOP);
	EXPORT_CONST_VALUE(DT_LEFT);
	EXPORT_CONST_VALUE(DT_RIGHT);
	EXPORT_CONST_VALUE(DT_BOTTOM);
	EXPORT_CONST_VALUE(DT_CENTER);
	EXPORT_CONST_VALUE(DT_VCENTER);


	EXPORT_CONST_VALUE(WM_LBUTTONDOWN);
	EXPORT_CONST_VALUE(WM_LBUTTONUP);
	EXPORT_CONST_VALUE(WM_RBUTTONDOWN);
	EXPORT_CONST_VALUE(WM_RBUTTONUP);


	EXPORT_CONST_VALUE(IDC_ARROW);
	EXPORT_CONST_VALUE(IDC_IBEAM);
	EXPORT_CONST_VALUE(IDC_WAIT);
	EXPORT_CONST_VALUE(IDC_CROSS);
	EXPORT_CONST_VALUE(IDC_UPARROW);
	EXPORT_CONST_VALUE(IDC_SIZE);
	EXPORT_CONST_VALUE(IDC_ICON);
	EXPORT_CONST_VALUE(IDC_SIZENWSE);
	EXPORT_CONST_VALUE(IDC_SIZENESW);
	EXPORT_CONST_VALUE(IDC_SIZEWE);
	EXPORT_CONST_VALUE(IDC_SIZENS);
	EXPORT_CONST_VALUE(IDC_SIZEALL);
	EXPORT_CONST_VALUE(IDC_NO);


	EXPORT_CONST_VALUE(UILIB_FILE);
	EXPORT_CONST_VALUE(UILIB_ZIP);
	EXPORT_CONST_VALUE(UILIB_RESOURCE);
	EXPORT_CONST_VALUE(UILIB_ZIPRESOURCE);

	EXPORT_CONST_VALUE(WM_USER);


	EXPORT_CONST_VALUE(MB_OK);
	EXPORT_CONST_VALUE(MB_OKCANCEL);
	EXPORT_CONST_VALUE(MB_ABORTRETRYIGNORE);
	EXPORT_CONST_VALUE(MB_YESNOCANCEL);
	EXPORT_CONST_VALUE(MB_YESNO);
	EXPORT_CONST_VALUE(MB_RETRYCANCEL);
	EXPORT_CONST_VALUE(MB_CANCELTRYCONTINUE);
	EXPORT_CONST_VALUE(MB_ICONHAND);
	EXPORT_CONST_VALUE(MB_ICONQUESTION);
	EXPORT_CONST_VALUE(MB_ICONEXCLAMATION);
	EXPORT_CONST_VALUE(MB_ICONASTERISK);


	EXPORT_CONST_VALUE(IDABORT);
	EXPORT_CONST_VALUE(IDCANCEL);
	EXPORT_CONST_VALUE(IDCONTINUE);
	EXPORT_CONST_VALUE(IDIGNORE);
	EXPORT_CONST_VALUE(IDNO);
	EXPORT_CONST_VALUE(IDOK);
	EXPORT_CONST_VALUE(IDRETRY);
	EXPORT_CONST_VALUE(IDTRYAGAIN);
	EXPORT_CONST_VALUE(IDYES);


	EXPORT_CONST_VALUE(MENU_ALIGN_LEFT);
	EXPORT_CONST_VALUE(MENU_ALIGN_TOP);
	EXPORT_CONST_VALUE(MENU_ALIGN_RIGHT);
	EXPORT_CONST_VALUE(MENU_ALIGN_BOTTOM);
}


}//namespace
