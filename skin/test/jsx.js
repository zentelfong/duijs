
/*
globalThis.JSX = function(tag,atts,kids) {
  return [tag,atts,kids]; // just produce "vnode" tuple
}
var t1  = <div>test</div>; 
print(t1)
*/


var t1  = <label name="test" text="hello"></label>; 

print(t1.getName());

t1.delete();
