import { Storage } from "DuiLib";

async function testStorage(){
    let storage = new Storage();
    let code = await storage.open("test.db");
    print("open test.db",code);
    let rslt = await storage.exec("select * from test");
    print("select",rslt.code,rslt.data);
    code = await storage.close();
    print("close test.db",code);
}

testStorage();