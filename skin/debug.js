import * as dui from "DuiLib"

const escapeSql = dui.String.excapeSql;

class DebugWindow extends dui.Window{

	constructor(){
		super();
	}

	async initWindow(){
		let mgr = this.manager;
		this.editOut = mgr.findControl("editOut");
		this.editInput = mgr.findControl("editInput");
		this.storage = new dui.Storage();

		let path = dui.getAppDataPath("DuiJs") + "debug.db";
		let code = await this.storage.open(path);
		if(code !=0 ){
			await this.storage.open(":memory:");
		}
		await this.storage.exec("CREATE TABLE IF NOT EXISTS Config(key TEXT,value TEXT,PRIMARY KEY (key))");
		let data = await this.storage.exec("SELECT* FROM Config");
		if(data.code == 0){
			this.print(data.data);
			let result = JSON.parse(data.data);
			if(result.length > 0){
				this.editInput.setText(result[0].value);
			}
		}else{
			this.print(`error:${data.code}`);
		}
		this.print(data);
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
			this.storage.exec(`REPLACE INTO Config(key,value) VALUES ('debugInput','${escapeSql(text)}')`);
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

debug.print("APP_DATA_PATH:",dui.getAppDataPath("DuiJs"));


