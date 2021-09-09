import {Window,Label,setResourcePath,postQuitMessage, Timer} from "DuiLib"

class TestWindow extends Window{
	constructor(){
		super();
		this.test();
	}
	
	async test(){
		this.timer = new Timer();

		let onTimer = ()=>{
			print("timerout****");
			this.timer.setTimer(onTimer,1000);
		}
		this.timer.setTimer(onTimer,1000);

		//await this.timer.wait(3000);
		//print("wait go on");
	}


	getSkinFile(){
		return "popup.xml";
	}
	
	onDestroy(){
		postQuitMessage(0);
	}

	createControl(cname){
		let label =  new Label();
		label.setText("hello");
		return label;
	}

	gotoWeb(){
		print("goto web");
		this.close();
	}
}

let testWindow = new TestWindow();

testWindow.create("test window");
testWindow.centerWindow();
testWindow.showWindow();

let label = testWindow.manager.findControl("testLabel");
label.setTextColor(0xff0000);



