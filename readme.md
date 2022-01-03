![](https://gitee.com/zentel/duijs/raw/dev/logo.png)

​    duijs（duilib for javascript），使用javascript来编写windows客户端程序。为了方便duilib者使用本库，JS中的函数命名和duilib库的C++函数名一致，并提供了接口声明文件，在vscode中接口可以自动补全。duilib使用的是[DuiLib_Ultimate](https://github.com/qdtroy/DuiLib_Ultimate)版本，并修改了部分代码。

**特性：**

1. 使用轻量的quickjs（支持ES2020标准）引擎；

2. 导出了duilib的90%以上的接口供JS调用（注：绘制相关接口未导出）；

3. 有完整的js接口文件，良好的编辑器代码提示；

4. 控件的事件无需在Notify函数中处理，通过控件属性绑定函数名称来处理；

5. 支持异步本地存储，读写操作不影响界面线程；

6. 支持http接口请求；

7. JS代码可以打包到资源文件中，换肤更灵活；

8. 控件属性支持css样式；

9. 支持编译成32位或者64位软件；

10. JS引擎支持加载dll插件；

11. JS调试输出工具，方便测试程序；

12. 支持编写typescript后编译为javascript运行；

13. jsx支持，当添加list的element时，可以直接在js代码中使用xml的写法生成element。（注意标签的首字母需要小写）

    

#### JSX

在typescript中使用jsx时，需要将ts后缀名改为tsx，tsc编译后会生成后缀名为jsx的文件，import时需注意后缀名。

