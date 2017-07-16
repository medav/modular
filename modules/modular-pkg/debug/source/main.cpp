
#include <iostream>
#include <memory>

#include "modular.h"
#include "module-interface.h"
#include "debug-protocol.h"

ModuleServices * services;
std::unique_ptr<DebugProtocol> debug;

void ModuleInitialize(ModuleServices * _services) {
    services = _services;
    debug.reset(new DebugProtocol);
    services->InstallProtocol((Protocol *) debug.get());
}

void ModuleStart() {
    debug->Debug("Debug module start");
}

EXPORT ModuleDispatch ModuleLoad() {
    ModuleDispatch dispatch;
    dispatch.Initialize = ModuleInitialize;
    dispatch.Start = ModuleStart;
    dispatch.Main = nullptr;
    return dispatch;
}