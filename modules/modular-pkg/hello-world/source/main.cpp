
#include <iostream>
#include <memory>

#include "modular.h"
#include "module-interface.h"
#include "debug-protocol.h"

ModuleServices * services;
DebugProtocol * debug;

void ModuleInitialize(ModuleServices * _services) {
    services = _services;
}

void ModuleStart() {
    debug = static_cast<DebugProtocol *>(services->LookupProtocol("debug"));
}

int ModuleMain(int argc, char * argv[]) {
    debug->Debug("Hello, Modular!");
    return 0;
}


EXPORT ModuleDispatch ModuleLoad() {
    ModuleDispatch dispatch;
    dispatch.Initialize = ModuleInitialize;
    dispatch.Start = ModuleStart;
    dispatch.Main = ModuleMain;
    return dispatch;
}