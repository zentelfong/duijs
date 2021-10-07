import { Timer } from "DuiLib";


/*
let timer = new Timer();

let count = 1;
let onTimer = ()=>{
    print(`OnTimer ${count}`);
    if(count < 10){
        timer.setTimer(onTimer,1000);
        count+=1;
    }else{
        //在这里赋值会立即回收timer内存，否则会等到执行gc时回收。
        timer = null;
    }
}
timer.setTimer(onTimer,1000);
*/



async function delayTest(){
    let delayTimer = new Timer();
    print("do task");
    await delayTimer.delay(1000);
    print("step");
    await delayTimer.delay(2000);
    print("finish task");
}

delayTest();
