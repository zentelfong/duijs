import * as dui from "DuiLib"
import { Config } from "./config.js"
import { format } from "./format.js"

class DebugWindow extends dui.Window{
	editOut:dui.RichEdit;
	editInput:dui.Edit;
	config:Config;
	lastInput?:string;

	constructor(){
		super();
	}

	//继承自父类
	async initWindow(){
		let mgr = this.manager;
		this.dragAcceptFiles(true);
		this.editOut = <dui.RichEdit>mgr.findControl("editOut");
		this.editInput = <dui.Edit>mgr.findControl("editInput");
		this.config = new Config();

		let path = dui.getAppDataPath("DuiJs") + "debug.db";
		await this.config.init(path);
		let lastInput = await this.config.get("Debug.lastInput");
		if(lastInput){
			this.editInput.setText(lastInput);
		}
	}
	
	getSkinFile(){
		return "debug.xml";
	}
	
	async onDestroy(){
		if(this.lastInput){
			await this.config.set("Debug.lastInput",this.lastInput);
		}
		await this.config.close();
		dui.postQuitMessage(0);
	}

	execJs(edit:dui.Edit){
		let text = edit.getText();
		try{
			dui.exec(text);
			this.lastInput = text;
		}catch(e){
			this.print(e);
		}
	}

	clickExec(btn:dui.Button){
		this.execJs(this.editInput);
	}

	print(text:string){
		this.editOut.appendText(text.toString());
		this.editOut.appendText("\n");
		this.editOut.endDown();
	}

	onDropFiles(list:[string]):void{
		let global = <any>globalThis;
		global._DEBUG = true;
		try{
			for (const file of list) {
				dui.execFile(file);
			}
		}catch(e){
			this.print(e);
		}
		global._DEBUG = false;
	}
}

let debugWindow = new DebugWindow();

debugWindow.create("DuiJs调试窗口",dui.WS_OVERLAPPEDWINDOW);
//debugWindow.manager.setDpi(144);
debugWindow.centerWindow();
debugWindow.showWindow();

globalThis.dui = dui;
globalThis.print = function() {
	debugWindow.print(format.apply(null, arguments));
}

//申明为全局
declare global{
	const _DEBUG:boolean;
	function print(...arg:any):void;
}

