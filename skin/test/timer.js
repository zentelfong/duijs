import { Timer } from "DuiLib";
async function delayTest() {
    let delayTimer = new Timer();
    print("do task");
    await delayTimer.delay(1000);
    print("step");
    await delayTimer.delay(2000);
    print("finish task");
}
delayTest();
