#include <nan.h>
#include "DisplayManager.h"

// Initialize a DisplayManager object which contains the Nan methods we need :)
NAN_MODULE_INIT(InitAll) {
    DisplayManager::Init(target);
}

NODE_MODULE(DisplayManager, InitAll)
