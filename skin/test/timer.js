import { Timer } from "DuiLib";
async function delayTest() {
    let delayTimer = new Timer();
    print("do task");
    await delayTimer.wait2(1000);
    print("step");
    await delayTimer.wait(2000);
    print("finish task");
}
delayTest();
