#include "Util.h"

namespace duijs {

void RegisterComboBox(qjs::Module* module) {
	DEFINE_CONTROL2(CComboBoxUI, CComboUI, "ComboBox");
}

}//namespace
