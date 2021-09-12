# duijs

duijs（duilib for javascript），使用javascript来编写windows客户端程序。为了方便duilib者使用本库，js中的函数命名和duilib库的C++函数名一致，并提供了typescript的接口文件，在vscode中接口可以自动补全。

**特性：**

1. 使用轻量的quickjs引擎实现；

2. 导出了duilib的90%以上的接口（绘制相关接口未导出）；
3. js的接口命名保持和duilib一致的命名（注意js中函数的首字母使用小写）；
4. 控件的事件无需在Notify函数中处理，通过控件属性绑定函数来处理；
5. 支持异步本地存储，读写操作不影响界面线程；



