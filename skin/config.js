import { Storage } from "DuiLib";
export class Config extends Storage {
    constructor() {
        super();
    }
    async init(path) {
        let code = await this.open(path);
        if (code != 0) {
            await this.open(":memory:");
        }
        await this.exec("CREATE TABLE IF NOT EXISTS Config(key TEXT,value TEXT,PRIMARY KEY (key))");
    }
    async get(key) {
        let data = await this.exec(`SELECT * FROM Config WHERE key = '${this.escape(key)}'`);
        if (data.code == 0 && data.data.length > 0) {
            return data.data[0].value;
        }
        return null;
    }
    async set(key, value) {
        let data = await this.exec(`REPLACE INTO Config(key,value) VALUES ('${this.escape(key)}','${this.escape(value)}')`);
        return data.code == 0;
    }
}
