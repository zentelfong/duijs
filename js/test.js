import {Window,setResourcePath,postQuitMessage} from "DuiLib"

setResourcePath("../skin/");

class TestWindow extends Window{
	
	constructor(){
		super();
		
		print(this.manager.getName());
	}
	
	getSkinFile(){
		return "popup.xml";
	}
	
	onDestroy(){
		postQuitMessage(0);
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




