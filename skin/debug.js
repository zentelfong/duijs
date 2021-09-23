import * as dui from "DuiLib";
import { Config } from "./config.js";
class DebugWindow extends dui.Window {
    constructor() {
        super();
    }
    async initWindow() {
        let mgr = this.manager;
        this.editOut = mgr.findControl("editOut");
        this.editInput = mgr.findControl("editInput");
        this.config = new Config();
        let path = dui.getAppDataPath("DuiJs") + "debug.db";
        await this.config.init(path);
        let lastInput = await this.config.get("Debug.lastInput");
        if (lastInput) {
            this.editInput.setText(lastInput);
        }
    }
    getSkinFile() {
        return "debug.xml";
    }
    async onDestroy() {
        await this.config.close();
        dui.postQuitMessage(0);
    }
    execJs(edit) {
        let text = edit.getText();
        try {
            dui.exec(text);
            this.config.set("Debug.lastInput", text);
        }
        catch (e) {
            this.print(e);
        }
    }
    print(...values) {
        for (const text of values) {
            this.editOut.appendText(text.toString());
            this.editOut.appendText("  ");
        }
        this.editOut.appendText("\n");
        this.editOut.endDown();
    }
}
let debugWindow = new DebugWindow();
debugWindow.create("DuiJs调试窗口", dui.WS_OVERLAPPEDWINDOW);
debugWindow.centerWindow();
debugWindow.showWindow();
globalThis.debug = debugWindow;
debugWindow.print("APP_DATA_PATH:", dui.getAppDataPath("DuiJs"));
