#include "quickjs/qjs.h"
#include "duilib/UIlib.h"

namespace duijs {

void RegisterConst(qjs::Module* module) {

	module->ExportUint32("WS_OVERLAPPED", WS_OVERLAPPED);
	module->ExportUint32("WS_POPUP", WS_POPUP);
	module->ExportUint32("WS_CHILD", WS_CHILD);
	module->ExportUint32("WS_MINIMIZE", WS_MINIMIZE);
	module->ExportUint32("WS_VISIBLE", WS_VISIBLE);
	module->ExportUint32("WS_DISABLED", WS_DISABLED);
	module->ExportUint32("WS_CLIPSIBLINGS", WS_CLIPSIBLINGS);
	module->ExportUint32("WS_CLIPCHILDREN", WS_CLIPCHILDREN);
	module->ExportUint32("WS_MAXIMIZE", WS_MAXIMIZE);
	module->ExportUint32("WS_CAPTION", WS_CAPTION);
	module->ExportUint32("WS_BORDER", WS_BORDER);
	module->ExportUint32("WS_DLGFRAME", WS_DLGFRAME);
	module->ExportUint32("WS_VSCROLL", WS_VSCROLL);
	module->ExportUint32("WS_HSCROLL", WS_HSCROLL);
	module->ExportUint32("WS_SYSMENU", WS_SYSMENU);
	module->ExportUint32("WS_THICKFRAME", WS_THICKFRAME);
	module->ExportUint32("WS_GROUP", WS_GROUP);
	module->ExportUint32("WS_TABSTOP", WS_TABSTOP);
	module->ExportUint32("WS_MINIMIZEBOX", WS_MINIMIZEBOX);

	module->ExportUint32("WS_MAXIMIZEBOX", WS_MAXIMIZEBOX);
	module->ExportUint32("WS_TILED", WS_TILED);
	module->ExportUint32("WS_ICONIC", WS_ICONIC);
	module->ExportUint32("WS_SIZEBOX", WS_SIZEBOX);
	module->ExportUint32("WS_TILEDWINDOW", WS_TILEDWINDOW);
	module->ExportUint32("WS_OVERLAPPEDWINDOW", WS_OVERLAPPEDWINDOW);
	module->ExportUint32("WS_POPUPWINDOW", WS_POPUPWINDOW);
	module->ExportUint32("WS_CHILDWINDOW", WS_CHILDWINDOW);


	module->ExportUint32("WS_EX_DLGMODALFRAME", WS_EX_DLGMODALFRAME);
	module->ExportUint32("WS_EX_NOPARENTNOTIFY", WS_EX_NOPARENTNOTIFY);
	module->ExportUint32("WS_EX_TOPMOST", WS_EX_TOPMOST);
	module->ExportUint32("WS_EX_ACCEPTFILES", WS_EX_ACCEPTFILES);
	module->ExportUint32("WS_EX_TRANSPARENT", WS_EX_TRANSPARENT);
	module->ExportUint32("WS_EX_MDICHILD", WS_EX_MDICHILD);
	module->ExportUint32("WS_EX_TOOLWINDOW", WS_EX_TOOLWINDOW);
	module->ExportUint32("WS_EX_WINDOWEDGE", WS_EX_WINDOWEDGE);
	module->ExportUint32("WS_EX_CLIENTEDGE", WS_EX_CLIENTEDGE);
	module->ExportUint32("WS_EX_CONTEXTHELP", WS_EX_CONTEXTHELP);
	module->ExportUint32("WS_EX_RIGHT", WS_EX_RIGHT);
	module->ExportUint32("WS_EX_LEFT", WS_EX_LEFT);
	module->ExportUint32("WS_EX_RTLREADING", WS_EX_RTLREADING);
	module->ExportUint32("WS_EX_LTRREADING", WS_EX_LTRREADING);
	module->ExportUint32("WS_EX_LEFTSCROLLBAR", WS_EX_LEFTSCROLLBAR);
	module->ExportUint32("WS_EX_RIGHTSCROLLBAR", WS_EX_RIGHTSCROLLBAR);
	module->ExportUint32("WS_EX_CONTROLPARENT", WS_EX_CONTROLPARENT);
	module->ExportUint32("WS_EX_STATICEDGE", WS_EX_STATICEDGE);
	module->ExportUint32("WS_EX_APPWINDOW", WS_EX_APPWINDOW);
	module->ExportUint32("WS_EX_OVERLAPPEDWINDOW", WS_EX_OVERLAPPEDWINDOW);

	module->ExportUint32("WS_EX_PALETTEWINDOW", WS_EX_PALETTEWINDOW);
	module->ExportUint32("WS_EX_LAYERED", WS_EX_LAYERED);
	module->ExportUint32("WS_EX_NOINHERITLAYOUT", WS_EX_NOINHERITLAYOUT);
	module->ExportUint32("WS_EX_LAYOUTRTL", WS_EX_LAYOUTRTL);
	module->ExportUint32("WS_EX_COMPOSITED", WS_EX_COMPOSITED);
	module->ExportUint32("WS_EX_NOACTIVATE", WS_EX_NOACTIVATE);

	module->ExportUint32("MK_CONTROL", MK_CONTROL);
	module->ExportUint32("MK_MBUTTON", MK_MBUTTON);
	module->ExportUint32("MK_RBUTTON", MK_RBUTTON);
	module->ExportUint32("MK_SHIFT", MK_SHIFT);
	module->ExportUint32("MK_XBUTTON1", MK_XBUTTON1);
	module->ExportUint32("MK_XBUTTON2", MK_XBUTTON2);


	module->ExportUint32("DT_TOP", DT_TOP);
	module->ExportUint32("DT_LEFT", DT_LEFT);
	module->ExportUint32("DT_RIGHT", DT_RIGHT);
	module->ExportUint32("DT_BOTTOM", DT_BOTTOM);
	module->ExportUint32("DT_CENTER", DT_CENTER);
	module->ExportUint32("DT_VCENTER", DT_VCENTER);


	module->ExportUint32("IDC_ARROW", (uint32_t)IDC_ARROW);
	module->ExportUint32("IDC_IBEAM", (uint32_t)IDC_IBEAM);
	module->ExportUint32("IDC_WAIT", (uint32_t)IDC_WAIT);
	module->ExportUint32("IDC_CROSS", (uint32_t)IDC_CROSS);
	module->ExportUint32("IDC_UPARROW", (uint32_t)IDC_UPARROW);
	module->ExportUint32("IDC_SIZE", (uint32_t)IDC_SIZE);
	module->ExportUint32("IDC_ICON", (uint32_t)IDC_ICON);
	module->ExportUint32("IDC_SIZENWSE", (uint32_t)IDC_SIZENWSE);
	module->ExportUint32("IDC_SIZENESW", (uint32_t)IDC_SIZENESW);
	module->ExportUint32("IDC_SIZEWE", (uint32_t)IDC_SIZEWE);
	module->ExportUint32("IDC_SIZENS", (uint32_t)IDC_SIZENS);
	module->ExportUint32("IDC_SIZEALL", (uint32_t)IDC_SIZEALL);
	module->ExportUint32("IDC_NO", (uint32_t)IDC_NO);


}


}//namespace
