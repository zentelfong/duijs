import {Window,Label,postQuitMessage, Timer,Storage, runGC ,WS_OVERLAPPEDWINDOW,messageBox, MB_OKCANCEL} from "DuiLib"

class TestWindow extends Window{
	constructor(){
		super();
		this.test();
	}
	
	async test(){
		this.timer = new Timer();

		let count = 1;
		let onTimer = ()=>{
			print("timerout****");
			this.timer.setTimer(onTimer,1000);
			let qrcode = this.manager.findControl("qrcode")
			qrcode.setText("test text " + count);
			count+=1;
		}
		this.timer.setTimer(onTimer,1000);

		//await this.timer.wait(3000);
		//print("wait go on");
	}


	getSkinFile(){
		return "popup.xml";
	}
	
	onDestroy(){
		this.timer.killTimer();
		//postQuitMessage(0);
	}

	createControl(cname){
		let label =  new Label();
		label.setText("你好");
		return label;
	}

	gotoWeb(){
		print("run gc");
		runGC();

		let rslt = messageBox(this,"进行垃圾回收？","提示",MB_OKCANCEL);
		print("rslt",rslt);
	}
}

let testWindow = new TestWindow();

testWindow.create("test window",WS_OVERLAPPEDWINDOW);
testWindow.centerWindow();
testWindow.showWindow();

let label = testWindow.manager.findControl("testLabel");
label.setTextColor(0xff0000);

async function testStorage(){
	let storage = new Storage();
	let code = await storage.open("test.db");
	print("open test.db",code);
	let rslt = await storage.exec("select * from test");
	print("select",rslt.code,rslt.data);
	code = await storage.close();
	print("close test.db",code);
}

testStorage();

