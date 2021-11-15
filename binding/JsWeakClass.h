#include "quickjs/qjs.h"
#include "duilib/UIlib.h"

namespace qjs {
using namespace DuiLib;

template<class T>
class WeakClass {
public:
	Class(JSContext* context, Module* module, const char* name)
		:context_(context),
		prototype_(context, JS_NewObject(context)),
		module_(module), class_inited_(false), class_name_(name)
	{
		if (class_id_ == 0) {
			JS_NewClassID(&class_id_);
		}
	}

	~Class() {
		assert(class_inited_);
	}


	void SetThis(JSValueConst this_val, T* pThis) {
		pThis->RefWeak();//添加弱引用
		qjs::SetThis(this_val, pThis->WeakImpl());
	}

	bool GetThis(JSValueConst this_val, T** pThis, JSClassID cid = 0) {
		CWeakImpl<T>* s = nullptr;
		return qjs::GetThis(this_val, &s, cid) ? s->ptr : nullptr;
	}

	//转为c
	static T* ToC(const Value& v) {
		T* pThis = nullptr;
		return GetThis(v, &pThis, class_id_) ? pThis : nullptr;
	}

	//创建新的js对象，注意js对象释放时会调用dtor释放ptr
	static Value ToJs(Context& context, T* ptr) {
		if (!ptr)
			return null_value;

		Value obj = context.NewＣlassObject(class_id_);
		SetThis(obj, ptr);
		return obj;
	}

	static Value ToJsById(Context& context, T* ptr, JSClassID cid) {
		if (!ptr)
			return null_value;
		//TODO:检测cid为class_id_的子类
		Value obj = context.NewＣlassObject(cid);
		SetThis(obj, ptr);
		return obj;
	}

	void Init(JSClassID parent_id = 0) {
		assert(!class_inited_);
		JSClassDef class_def = {
			class_name_,[](JSRuntime* rt, JSValue val) {
				CWeakImpl<T>* s = nullptr;
				if (::GetThis(val, &s)) {
					s->Release();
				}
			},nullptr,nullptr,nullptr
		};
		NewClass(&class_def, parent_id);
	}

	void AddCtor() {
		JSValue constructor = JS_NewCFunction2(context_, [](JSContext* ctx,
			JSValueConst new_target,
			int argc, JSValueConst* argv) {

				Value proto(ctx, JS_GetPropertyStr(ctx, new_target, "prototype"));
				if (proto.IsException()) {
					return JS_EXCEPTION;
				}
				Context* context = Context::get(ctx);
				ArgList arg_list(ctx, argc, argv);
				T* pThis = new T;
				if (!pThis) {
					return JS_ThrowInternalError(ctx, "ctor error");
				}

				Value obj(ctx, JS_NewObjectProtoClass(ctx, proto, class_id_));

				if (obj.IsException()) {
					return JS_EXCEPTION;
				}
				SetThis(obj, pThis);
				return obj.Release();
			}, class_name_, 0, JS_CFUNC_constructor, 0);
		JS_SetConstructor(context_, constructor, prototype_);
		module_->Export(class_name_, constructor);
	}

	template<Value func(T* pThis, Context& context, ArgList& args)>
	void AddFunc(const char* name) {
		JS_DefinePropertyValueStr(context_, prototype_, name,
			JS_NewCFunction(context_,
				[](JSContext* ctx, JSValueConst this_val, int argc, JSValueConst* argv) {
					T* pThis = nullptr;
					if (!GetThis(this_val, &pThis)) {
						return JS_ThrowTypeError(ctx, "no this pointer exist");
					}
					Context* context = Context::get(ctx);
					ArgList arg_list(ctx, argc, argv);
					return func(pThis, *context, arg_list).Release();
				}, name, 0), 0);
	}

	template<JSCFunction func>
	void AddCFunc(const char* name) {
		JS_DefinePropertyValueStr(context_, prototype_, name, JS_NewCFunction(context_, func, name, 0));
	}

	template<Value get(T* pThis, Context& context), void set(T* pThis, Value arg)>
	void AddGetSet(const char* name) {
		JSCFunctionType get_func;
		get_func.getter = [](JSContext* ctx, JSValueConst this_val) {
			T* pThis = nullptr;
			if (!GetThis(this_val, &pThis)) {
				JS_ThrowTypeError(ctx, "no this pointer exist");
				return JS_EXCEPTION;
			}

			Context* context = Context::get(ctx);
			return get(pThis, *context).Release();
		};

		JSValue get_func_value = JS_NewCFunction2(context_, get_func.generic, name, 0, JS_CFUNC_getter, 0);


		JSCFunctionType set_func;
		set_func.setter = [](JSContext* ctx, JSValueConst this_val, JSValueConst val) {
			T* pThis = nullptr;
			if (!GetThis(this_val, &pThis)) {
				JS_ThrowTypeError(ctx, "no this pointer exist");
				return JS_EXCEPTION;
			}
			Value arg(ctx, val);
			set(pThis, arg);
			return JS_UNDEFINED;
		};

		JSValue set_func_value = JS_NewCFunction2(context_, set_func.generic, name, 1, JS_CFUNC_setter, 0);
		auto atom = JS_NewAtom(context_, name);
		JS_DefinePropertyGetSet(context_, prototype_, atom, get_func_value, set_func_value, 0);
		JS_FreeAtom(context_, atom);
	}


	template<Value get(T* pThis, Context& context)>
	void AddGet(const char* name) {
		JSCFunctionType get_func;
		get_func.getter = [](JSContext* ctx, JSValueConst this_val) {
			T* pThis = nullptr;
			if (!GetThis(this_val, &pThis)) {
				JS_ThrowTypeError(ctx, "no this pointer exist");
				return JS_EXCEPTION;
			}

			Context* context = Context::get(ctx);
			return get(pThis, *context).Release();
		};

		JSValue get_func_value = JS_NewCFunction2(context_, get_func.generic, name, 0, JS_CFUNC_getter, 0);

		auto atom = JS_NewAtom(context_, name);

		JS_DefineProperty(context_, prototype_, atom, JS_UNDEFINED, get_func_value, JS_UNDEFINED,
			JS_PROP_HAS_GET | JS_PROP_HAS_CONFIGURABLE | JS_PROP_HAS_ENUMERABLE);
		JS_FreeValue(context_, get_func_value);
		JS_FreeAtom(context_, atom);
	}

	template<void set(T* pThis, Value arg)>
	void AddSet(const char* name) {
		JSCFunctionType set_func;
		set_func.setter = [](JSContext* ctx, JSValueConst this_val, JSValueConst val) {
			T* pThis = nullptr;
			if (!GetThis(this_val, &pThis)) {
				JS_ThrowTypeError(ctx, "no this pointer exist");
				return JS_EXCEPTION;
			}
			Value arg(ctx, val);
			set(pThis, arg);
			return JS_UNDEFINED;
		};

		JSValue set_func_value = JS_NewCFunction2(context_, set_func.generic, name, 1, JS_CFUNC_setter, 0);
		auto atom = JS_NewAtom(context_, name);
		JS_DefineProperty(context_, prototype_, atom, JS_UNDEFINED, JS_UNDEFINED, set_func_value,
			JS_PROP_HAS_SET | JS_PROP_HAS_CONFIGURABLE | JS_PROP_HAS_ENUMERABLE);
		JS_FreeValue(context_, set_func_value);
		JS_FreeAtom(context_, atom);
	}

	template<Value itr(T* pThis, Context& context, ArgList& arglist, bool& finish)>
	void AddIterator(const char* name) {
		JSCFunctionType itr_func;
		itr_func.iterator_next = [](JSContext* ctx, JSValueConst this_val,
			int argc, JSValueConst* argv, int* pdone, int magic) {
				T* pThis = nullptr;
				if (!GetThis(this_val, &pThis)) {
					JS_ThrowTypeError(ctx, "no this pointer exist");
					return JS_EXCEPTION;
				}

				Context* context = Context::get(ctx);
				ArgList arg_list(ctx, argc, argv);
				bool finish = false;
				Value result = itr(pThis, *context, arg_list, finish);
				*pdone = finish;
				return result.Release();
		};

		JSValue itr_func_value = JS_NewCFunction2(context_, itr_func.generic, name, 0, JS_CFUNC_iterator_next, 0);
		auto atom = JS_NewAtom(context_, name);
		JS_DefinePropertyValue(context_, prototype_, atom, itr_func_value, 0);
		JS_FreeAtom(context_, atom);
	}


	//添加属性等
	void AddValue(const char* name, const Value& value) {
		JS_DefinePropertyValueStr(context_, prototype_, name, value.CopyValue(), 0);
	}

	void AddString(const char* name, const char* value) {
		JS_DefinePropertyValueStr(context_, prototype_, name, JS_NewString(context_, value), 0);
	}

	void AddString(const char* name, const char* value, size_t len) {
		JS_DefinePropertyValueStr(context_, prototype_, name, JS_NewStringLen(context_, value, len), 0);
	}

	void AddInt32(const char* name, int32_t value) {
		JS_DefinePropertyValueStr(context_, prototype_, name, JS_NewInt32(context_, value), 0);
	}

	void AddInt64(const char* name, int32_t value) {
		JS_DefinePropertyValueStr(context_, prototype_, name, JS_NewInt64(context_, value), 0);
	}

	void AddFloat(const char* name, float value) {
		JS_DefinePropertyValueStr(context_, prototype_, name, JS_NewFloat64(context_, value), 0);
	}

	void AddFloat64(const char* name, double value) {
		JS_DefinePropertyValueStr(context_, prototype_, name, JS_NewFloat64(context_, value), 0);
	}

	static JSClassID class_id() {
		return class_id_;
	}


private:
	void NewClass(JSClassDef* class_def, JSClassID parent_id = 0) {
		assert(!class_inited_);
		JS_NewClass(JS_GetRuntime(context_), class_id_, class_def);
		JS_SetClassProto(context_, class_id_, prototype_.CopyValue());
		class_inited_ = true;

		if (parent_id) {
			ClassIdManager::Instance()->AddClass(class_id_, parent_id);

			JSValue parent = JS_GetClassProto(context_, parent_id);
			if (JS_IsObject(parent)) {
				JS_SetPrototype(context_, prototype_, parent);
			}
			else {
				JS_ThrowInternalError(context_, "invalied parent class id %u", parent_id);
			}
			JS_FreeValue(context_, parent);
		}
	}


	static JSClassID class_id_;

	JSContext* context_;
	Value prototype_;
	Module* module_;
	bool class_inited_;
	const char* class_name_;
};


}//namespace

