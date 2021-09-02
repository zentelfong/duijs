#pragma once
#include "quickjs/qjs.h"


namespace DuiLib {
class CControlUI;
}//namesapce

namespace duijs {

void RegisterControl(qjs::Module* module);
qjs::Value toValue(qjs::Context& ctx, DuiLib::CControlUI* control);


}//namesapce

