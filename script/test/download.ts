import { FileDownload } from "DuiLib";

class TestDownload extends FileDownload{
    constructor(url:string,path:string){
        super(url,path);
    }
    progress(total:number,download:number):void{
        print("process:",total,download);
    }

    finish(path:string):void{
        print("download finish:",path);
    }
    faild():void{
        print("download faild");
    }
}

let download = new TestDownload("https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png","test.png");
download.start();

