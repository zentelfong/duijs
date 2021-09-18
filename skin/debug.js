import * as dui from "DuiLib"

class DebugWindow extends dui.Window{

	constructor(){
		super();
	}

	initWindow(){
		let mgr = this.manager;
		this.editOut = mgr.findControl("editOut");
	}
	
	getSkinFile(){
		return "debug.xml";
	}
	
	onDestroy(){
		dui.postQuitMessage(0);
	}

	execJs(edit){
		let text = edit.getText();
		try{
			dui.exec(text);
		}catch(e){
			this.print(e);
		}
	}

	print(...values){
		for (const text of values) {
			this.editOut.appendText(text.toString());
			this.editOut.appendText("  ");
		}
		this.editOut.appendText("\n");
		this.editOut.endDown();
	}
}
// debug.print(3213213);

let debugWindow = new DebugWindow();

debugWindow.create("DuiJs调试窗口",dui.WS_OVERLAPPEDWINDOW);
debugWindow.centerWindow();
debugWindow.showWindow();
globalThis.debug = debugWindow;

