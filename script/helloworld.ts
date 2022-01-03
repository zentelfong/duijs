import * as dui from "DuiLib";
class HelloWindow extends dui.Window {
    constructor() {
        super();
    }
    getSkinFile() {
        return "helloworld.xml";
    }
}
let window = new HelloWindow();
window.create("HelloWorld", dui.WS_OVERLAPPEDWINDOW);
window.centerWindow();
window.showWindow(true,true);
