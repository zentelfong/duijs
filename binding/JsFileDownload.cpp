#include "Util.h"
#include "network/FileDownload.h"
#include "JsTaskManager.h"

namespace duijs {

class JsFileDownload:public network::CurlDownloadListener,
    public network::CurlDownload {
public:
    JsFileDownload(Value& this_obj) {
        task_mgr_ = TaskManager::GetCurrent();
        this_ = new Value(this_obj);
    }

    ~JsFileDownload() {
        Value* value = this_;
        if (value) {
            task_mgr_->PostTask([value]() {
                //由主线程释放
                delete value;
            });
        }
    }

    void didProgress(int total, int size) override { 
        RefCountedPtr<JsFileDownload> pThis(this);
        if (pThis->this_) {
            task_mgr_->PostTask([pThis, total,size]() {
                if (pThis->this_ && pThis->this_->HasProperty("progress")) {
                    auto context = pThis->this_->context();
                    pThis->this_->Invoke("progress", 
                        context->NewInt32(total),
                        context->NewInt32(size));
                }
            });
        }
    }

    void didFinish() override { 
        RefCountedPtr<JsFileDownload> pThis(this);
        if (pThis->this_) {
            task_mgr_->PostTask([pThis]() {
                if (pThis->this_ && pThis->this_->HasProperty("finish")) {
                    auto context = pThis->this_->context();
                    pThis->this_->Invoke("finish", context->NewString(pThis->getDestination().c_str()));
                }
                delete pThis->this_;
                pThis->this_ = nullptr;
            });
        }
    }

    void didFail() override { 
        RefCountedPtr<JsFileDownload> pThis(this);
        if (pThis->this_) {
            task_mgr_->PostTask([pThis]() {
                if (pThis->this_ && pThis->this_->HasProperty("faild")) {
                    pThis->this_->Invoke("faild");
                }
                delete pThis->this_;
                pThis->this_ = nullptr;
            });
        }
    }

private:
    TaskManager* task_mgr_;
    Value* this_;
};

//url,path
static JsFileDownload* createFileDownload(qjs::Context& context, Value& this_obj, qjs::ArgList& args) {

    if (args.size() != 2) {
        context.ThrowTypeError("arg must(url,path)");
        return nullptr;
    }

    JsFileDownload* download = new RefCountedObject<JsFileDownload>(this_obj);
    download->AddRef();
    download->init(download,args[0].ToStdString(),args[1].ToStdString());
    return download;
}

static void deleteDownload(JsFileDownload* w) {
    w->Release();
}

static Value start(JsFileDownload* pThis, Context& context, ArgList& args) {
    pThis->start();
    return undefined_value;
}

static Value cancel(JsFileDownload* pThis, Context& context, ArgList& args) {
    pThis->cancel();
    return undefined_value;
}


void RegisterFileDownload(qjs::Module* module) {
    auto cls = module->ExportClass<JsFileDownload>("FileDownload");
    cls.Init<deleteDownload>();
    cls.AddCtor2<createFileDownload>();
    cls.AddFunc<start>("start");
    cls.AddFunc<cancel>("cancel");
}


}//namespace

