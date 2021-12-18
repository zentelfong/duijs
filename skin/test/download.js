import { FileDownload } from "DuiLib";
class TestDownload extends FileDownload {
    constructor(url, path) {
        super(url, path);
    }
    progress(total, download) {
        print("process:", total, download);
    }
    finish(path) {
        print("download finish:", path);
    }
    faild() {
        print("download faild");
    }
}
let download = new TestDownload("https://www.baidu.com/img/PCtm_d9c8750bed0b3c7d089fa7d55720d6cf.png", "test.png");
download.start();
