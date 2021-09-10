#include "Util.h"

namespace duijs {


static Value setMultiLine(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetMultiLine(args[0].ToBool());
	return null_value;
}


static Value isMultiLine(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context,pThis->IsMultiLine());
}

static Value setWantTab(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetWantTab(args[0].ToBool());
	return null_value;
}


static Value isWantTab(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsWantTab());
}



static Value setWantReturn(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetWantReturn(args[0].ToBool());
	return null_value;
}


static Value isWantReturn(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsWantReturn());
}

static Value setWantCtrlReturn(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetWantCtrlReturn(args[0].ToBool());
	return null_value;
}


static Value isWantCtrlReturn(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsWantCtrlReturn());
}

static Value setTransparent(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetTransparent(args[0].ToBool());
	return null_value;
}


static Value isTransparent(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsTransparent());
}



static Value setRich(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetRich(args[0].ToBool());
	return null_value;
}


static Value isRich(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsRich());
}

static Value setReadOnly(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetReadOnly(args[0].ToBool());
	return null_value;
}


static Value isReadOnly(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsReadOnly());
}

static Value setWordWrap(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetWordWrap(args[0].ToBool());
	return null_value;
}


static Value isWordWrap(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsWordWrap());
}

static Value setFont(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetFont(args[0].ToInt32());
	return null_value;
}


static Value getFont(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFont());
}



static Value setWinStyle(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetWinStyle(args[0].ToInt32());
	return null_value;
}


static Value getWinStyle(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetWinStyle());
}

static Value setTextColor(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextColor(args[0].ToUint32());
	return null_value;
}


static Value getTextColor(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context,(uint32_t) pThis->GetTextColor());
}

static Value setLimitText(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetLimitText(args[0].ToInt32());
	return null_value;
}

static Value getLimitText(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetLimitText());
}

static Value getTextLength(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTextLength(args[0].ToUint32()));
}

static Value getText(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetText());
}

static Value setText(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetText(JsString(args[0]));
	return null_value;
}

static Value setModify(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetModify(args[0].ToBool());
	return null_value;
}

static Value isModify(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsModify());
}

static Value setModify(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetModify(args[0].ToBool());
	return null_value;
}

static Value getSel(CRichEditUI* pThis, Context& context, ArgList& args) {
	CHARRANGE cr;
	pThis->GetSel(cr);
	return toValue(context,cr);
}

static Value setSel(CRichEditUI* pThis, Context& context, ArgList& args) {
	if(args[0].IsObject())
		pThis->SetSel(toCharRange(args[0]));
	else
		pThis->SetSel(args[0].ToInt32(),args[1].ToInt32());
	return null_value;
}

static Value replaceSel(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->ReplaceSel(JsString(args[0]),args[1].ToBool());
	return null_value;
}

static Value getSelText(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetSelText());
}

static Value setSelAll(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelAll();
	return null_value;
}

static Value setSelNone(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetSelNone();
	return null_value;
}


static Value getSelectionType(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context,(int)pThis->GetSelectionType());
}


static Value getZoom(CRichEditUI* pThis, Context& context, ArgList& args) {
	int nNum, nDen;
	if (pThis->GetZoom(nNum, nDen)) {
		auto rslt = context.NewObject();
		rslt.SetPropertyInt32("num", nNum);
		rslt.SetPropertyInt32("den", nDen);
		return rslt;
	}
	return undefined_value;
}


static Value setZoom(CRichEditUI* pThis, Context& context, ArgList& args) {
	auto arg = args[0];
	if (arg.IsObject()) {
		pThis->SetZoom(arg.GetProperty("num").ToInt32(), 
			arg.GetProperty("den").ToInt32());
	}
	else {
		pThis->SetZoom(args[0].ToInt32(),
			args[1].ToInt32());
	}
	return null_value;
}


static Value setZoomOff(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetZoomOff();
	return null_value;
}

static Value getAutoURLDetect(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetAutoURLDetect());
}


static Value setAutoURLDetect(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetAutoURLDetect(args[0].ToBool());
	return null_value;
}

static Value getEventMask(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetEventMask());
}


static Value setEventMask(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetEventMask(args[0].ToUint32());
	return null_value;
}

static Value getTextRange(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTextRange(args[0].ToInt32(),args[1].ToInt32()));
}

static Value hideSelection(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->HideSelection(args[0].ToBool(),args[1].ToBool());
	return null_value;
}

static Value scrollCaret(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->ScrollCaret();
	return null_value;
}

static Value insertText(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->InsertText(args[0].ToInt32(),JsString(args[1]),args[2].ToBool()));
}

static Value appendText(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->AppendText(JsString(args[0]), args[1].ToBool()));
}


//
//DWORD GetDefaultCharFormat(CHARFORMAT2& cf) const;
//bool SetDefaultCharFormat(CHARFORMAT2& cf);
//DWORD GetSelectionCharFormat(CHARFORMAT2& cf) const;
//bool SetSelectionCharFormat(CHARFORMAT2& cf);
//bool SetWordCharFormat(CHARFORMAT2& cf);
//DWORD GetParaFormat(PARAFORMAT2& pf) const;
//bool SetParaFormat(PARAFORMAT2& pf);
//

static Value canUndo(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->CanUndo());
}

static Value canRedo(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->CanRedo());
}

static Value canPaste(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->CanPaste());
}

static Value redo(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->Redo());
}
static Value undo(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->Undo());
}

static Value clear(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->Clear();
	return null_value;
}

static Value copy(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->Copy();
	return null_value;
}

static Value cut(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->Cut();
	return null_value;
}

static Value paste(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->Paste();
	return null_value;
}

static Value getLineCount(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetLineCount());
}

static Value getLine(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetLine(args[0].ToInt32(),args[1].ToInt32()));
}

static Value lineIndex(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->LineIndex(args[0].ToInt32()));
}

static Value lineLength(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->LineLength(args[0].ToInt32()));
}

static Value lineScroll(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->LineScroll(args[0].ToInt32(),args[1].ToInt32()));
}

static Value getCharPos(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetCharPos(args[0].ToInt32()));
}


static Value lineFromChar(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->LineFromChar(args[0].ToInt32()));
}

static Value posFromChar(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->PosFromChar(args[0].ToUint32()));
}

static Value charFromPos(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->CharFromPos(toPoint(args[0])));
}

static Value emptyUndoBuffer(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->EmptyUndoBuffer();
	return null_value;
}


static Value setUndoLimit(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->SetUndoLimit(args[0].ToUint32()));
}


static Value setAccumulateDBCMode(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetAccumulateDBCMode(args[0].ToBool());
	return null_value;
}

static Value isAccumulateDBCMode(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->IsAccumulateDBCMode());
}


static Value setTextPadding(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetTextPadding(toRect(args[0]));
	return null_value;
}

static Value getTextPadding(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTextPadding());
}


static Value setNormalImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetNormalImage(JsString(args[0]));
	return null_value;
}

static Value getNormalImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetNormalImage());
}

static Value setHotImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetHotImage(JsString(args[0]));
	return null_value;
}

static Value getHotImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetHotImage());
}

static Value setFocusedImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetFocusedImage(JsString(args[0]));
	return null_value;
}

static Value getFocusedImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetFocusedImage());
}

static Value setDisabledImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetDisabledImage(JsString(args[0]));
	return null_value;
}

static Value getDisabledImage(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetDisabledImage());
}


static Value setTipValue(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetTipValue(JsString(args[0]));
	return null_value;
}

static Value getTipValue(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, pThis->GetTipValue());
}


static Value setTipValueColor(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetTipValueColor(args[0].ToUint32());
	return null_value;
}

static Value getTipValueColor(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetTipValueColor());
}

static Value setTipValueAlign(CRichEditUI* pThis, Context& context, ArgList& args) {
	pThis->SetTipValueAlign(args[0].ToUint32());
	return null_value;
}

static Value getTipValueAlign(CRichEditUI* pThis, Context& context, ArgList& args) {
	return toValue(context, (uint32_t)pThis->GetTipValueAlign());
}


void RegisterRichEdit(qjs::Module* module) {
	DEFINE_CONTROL2(CRichEditUI, CContainerUI, "RichEdit");
	
}


}//namespace
