import * as dui from "DuiLib"

class DebugWindow extends dui.Window{

	constructor(){
		super();
	}

	async initWindow(){
		let mgr = this.manager;
		this.editOut = mgr.findControl("editOut");

		this.storage = new dui.Storage();

		let path = dui.getAppDataPath("DuiJs") + "debug.db";
		let code = await this.storage.open(path);
		if(code !=0 ){
			await this.storage.open(":memory:");
		}

		//await this.storage.exec("CREATE TABLE IF NOT EXISTS Config()")
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

debug.print("APP_DATA_PATH:",dui.getAppDataPath("DuiJs"))


