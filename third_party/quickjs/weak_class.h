#pragma once
#include "qjs.h"
#include "weak_ptr.h"

namespace qjs {

template<class T>
bool GetSafeThis(Context* context, JSValueConst this_val, WeakPtr<T>* ptr,JSClassID cid) {
	if (!JS_IsObject(this_val)) {
		return false;
	}

	JSClassID id = JS_GetClassID(this_val);
	if (cid) {
		JSClassID pid = id;
		while (pid) {
			if (pid == cid) {
				//如果id或者其父class id与class_id_相同则允许转换
				*ptr = reinterpret_cast<WeakImpl<T>*>(JS_GetOpaque(this_val, id));
				return ptr->valid();
			}
			pid = context->GetParentClassId(pid);
		}
		return false;
	}
	*ptr = reinterpret_cast<WeakImpl<T>*>(JS_GetOpaque(this_val, id));
	return ptr->valid();
}


template<class T>
bool GetSafeThis(JSValueConst this_val, WeakPtr<T>* ptr) {
	if (!JS_IsObject(this_val)) {
		return false;
	}
	JSClassID id = JS_GetClassID(this_val);
	*ptr = reinterpret_cast<WeakImpl<T>*>(JS_GetOpaque(this_val, id));
	return ptr->valid();
}



template<class T>
inline void SetSafeThis(JSValueConst this_val, WeakPtr<T> pThis) {
	pThis.impl()->AddRef();
	JS_SetOpaque(this_val, pThis.impl());
}

//WeakClass 的对象由C++进行释放，js只保留弱引用
template<class T>
class WeakClass :public ClassBase {
public:
	WeakClass(JSContext* context, Module* module, const char* name)
		:ClassBase(context, module, name)
	{
		if (class_id_ == 0) {
			JS_NewClassID(&class_id_);
		}
	}

	//转为C指针，会校验classid
	static WeakPtr<T> ToC(const Value& v) {
		auto context = v.context();
		if (!context) {
			return nullptr;
		}
		WeakPtr<T> pThis;
		return GetSafeThis(context, v, &pThis, class_id_) ? pThis : nullptr;
	}

	//创建新的js对象，注意js对象释放时会调用dtor释放ptr
	static Value ToJs(Context& context, WeakPtr<T> ptr) {
		if (!ptr)
			return null_value;

		Value obj = context.NewＣlassObject(class_id_);
		SetSafeThis(obj, ptr);
		return obj;
	}


	static Value ToJsById(Context& context, WeakPtr<T> ptr, JSClassID cid) {
		if (!ptr)
			return null_value;
		//TODO:检测cid为class_id_的子类
		Value obj = context.NewＣlassObject(cid);
		SetSafeThis(obj, ptr);
		return obj;
	}


	void Init(JSClassFinalizer* finalizer, JSClassID parent_id = 0) {
		assert(!class_inited_);
		JSClassDef class_def = {
			class_name_,finalizer,nullptr,nullptr,nullptr
		};
		NewClass(&class_def, parent_id);
	}

	void Init(JSClassFinalizer* finalizer, JSClassGCMark* gc_mark, JSClassID parent_id = 0) {
		assert(!class_inited_);
		JSClassDef class_def = {
			class_name_,finalizer,gc_mark,nullptr,nullptr
		};
		NewClass(&class_def, parent_id);
	}

	void Init(JSClassID parent_id = 0) {
		assert(!class_inited_);

		JSClassDef class_def = {
			class_name_,[](JSRuntime* rt, JSValue val) {
				WeakPtr<T> s;
				if (GetSafeThis(val, &s)) {
					s.impl()->Release();
				}
			},nullptr,nullptr,nullptr
		};

		NewClass(&class_def, parent_id);
	}


	template<void mark(T*, JS_MarkFunc* mark_func)>
	void Init2(JSClassID parent_id = 0) {
		assert(!class_inited_);

		JSClassDef class_def = {
			class_name_,
			[](JSRuntime* rt, JSValue val) {
				WeakPtr<T> s;
				if (GetSafeThis(val,&s)) {
					s.impl()->Release();
				}
			},
			[](JSRuntime* rt, JSValueConst val, JS_MarkFunc* mark_func) {
				WeakPtr<T> s;
				if (GetSafeThis(val,&s)) {
					mark(s, mark_func);
				}
			},nullptr,nullptr
		};

		NewClass(&class_def, parent_id);
	}


	template<WeakPtr<T> ctor(Context& context, ArgList& args)>
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
				WeakPtr<T> pThis = ctor(*context, arg_list);
				if (!pThis) {
					return JS_ThrowInternalError(ctx, "ctor error");
				}

				Value obj(ctx, JS_NewObjectProtoClass(ctx, proto, class_id_));

				if (obj.IsException()) {
					return JS_EXCEPTION;
				}
				SetSafeThis(obj, pThis);
				return obj.Release();
			}, class_name_, 0, JS_CFUNC_constructor, 0);
		JS_SetConstructor(context_, constructor, prototype_);
		module_->Export(class_name_, constructor);
	}

	template<WeakPtr<T> ctor(Context& context, Value& this_obj, ArgList& args)>
	void AddCtor2() {
		JSValue constructor = JS_NewCFunction2(context_, [](JSContext* ctx,
			JSValueConst new_target,
			int argc, JSValueConst* argv) {

				Value proto(ctx, JS_GetPropertyStr(ctx, new_target, "prototype"));
				if (proto.IsException()) {
					return JS_EXCEPTION;
				}
				Context* context = Context::get(ctx);
				ArgList arg_list(ctx, argc, argv);

				Value obj(ctx, JS_NewObjectProtoClass(ctx, proto, class_id_));

				if (obj.IsException()) {
					return JS_EXCEPTION;
				}

				WeakPtr<T> pThis = ctor(*context, obj, arg_list);
				if (!pThis) {
					return JS_ThrowInternalError(ctx, "ctor error");
				}

				SetSafeThis(obj, pThis);
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
					WeakPtr<T> pThis;
					if (!GetSafeThis(this_val, &pThis)) {
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
			WeakPtr<T> pThis;
			if (!GetSafeThis(this_val, &pThis)) {
				JS_ThrowTypeError(ctx, "no this pointer exist");
				return JS_EXCEPTION;
			}

			Context* context = Context::get(ctx);
			return get(pThis, *context).Release();
		};

		JSValue get_func_value = JS_NewCFunction2(context_, get_func.generic, name, 0, JS_CFUNC_getter, 0);


		JSCFunctionType set_func;
		set_func.setter = [](JSContext* ctx, JSValueConst this_val, JSValueConst val) {
			WeakPtr<T> pThis;
			if (!GetSafeThis(this_val, &pThis)) {
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
			WeakPtr<T> pThis;
			if (!GetSafeThis(this_val, &pThis)) {
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
			WeakPtr<T> pThis;
			if (!GetSafeThis(this_val, &pThis)) {
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
				WeakPtr<T> pThis;
				if (!GetSafeThis(this_val, &pThis)) {
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
			Context::get(context_)->AddClassId(class_id_, parent_id);
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
};


template<class T>
JSClassID WeakClass<T>::class_id_ = 0;

template<class T>
WeakClass<T> Module::ExportWeakClass(const char* name) {
	return WeakClass<T>(context_, this, name);
}

}//namespace


