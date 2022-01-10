import * as dui from "DuiLib";
class ListWindow extends dui.Window {
    constructor() {
        super();
    }
    initWindow() {
        this.list = this.manager.findControl("list");
        for (let index = 0; index < 100; index++) {
            let item = <listlabelelement text={index}></listlabelelement>;
            this.list.add(item);
        }
    }
    getSkinFile() {
        return "list.xml";
    }
    selectItem(list, idx) {
        print("选择了：", idx);
    }
}
let listWindow = new ListWindow();
listWindow.create("List测试窗口", dui.WS_OVERLAPPEDWINDOW);
listWindow.centerWindow();
listWindow.showWindow(true, true);
