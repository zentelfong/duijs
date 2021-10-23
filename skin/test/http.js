import { HttpClient,HttpRequest } from "DuiLib";

let client = globalThis.client;
if(!client){
    client = new HttpClient();
    globalThis.client = client;
}

let req = new HttpRequest("https://www.baidu.com/");
req.setCallback((rep)=>{
    print(rep.code(),rep.headers());
});
client.get(req);
