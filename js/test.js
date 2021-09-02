import {Window,setResourcePath} from "DuiLib"

setResourcePath("../skin/");

class TestWindow extends Window{
	
	constructor(){
		super();
		
		print(this.manager.getName());
	}
	
	getSkinFile(){
		return "popup.xml";
	}
	
	gotoWeb(){
		print("goto web");
		this.close();
	}
}

let testWindow = new TestWindow();

testWindow.create("test window");
testWindow.showWindow();




