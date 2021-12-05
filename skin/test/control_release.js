import * as dui from "DuiLib";

//Control 控件在js中保存了弱引用，当C++中释放了Control时，js再操作该对象时只会抛出异常，不会崩溃
//如果对象在js中释放，C++中不会感知该对象已释放，操作该对象后可能导致崩溃。
//在js中创建的控件如果添加到界面显示，则由C++释放该对象，如果未添加到界面显示则需调用delete函数删除。
let text_control = new dui.Text();
text_control.setText("test");
text_control.delete(); //删除该对象

text_control.getText(); //会报no this pointer exist异常，不会崩溃

