#include <nan.h>
#include "DisplayManager.h"

NAN_MODULE_INIT(InitAll) {
	DisplayManager::Init(target);
}

NODE_MODULE(DisplayManager, InitAll)
