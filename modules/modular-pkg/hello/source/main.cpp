
#include <iostream>
#include <memory>

#include "modular.h"
#include "modular-debug.h"
#include "module-interface.h"
#include "logger-protocol.h"

ModuleServices * services;
std::shared_ptr<LoggerProtocol> logger_prot;

void ModuleInitialize(ModuleServices& _services) {
    services = &_services;
}

void ModuleStart() {
    logger_prot = std::dynamic_pointer_cast<LoggerProtocol>(services->LookupProtocol("logger"));
}

int ModuleMain(int argc, char * argv[]) {
    logger_prot->Log("Hello, Modular!");
    return 0;
}

EXPORT ModuleDispatch ModuleLoad() {
    ModuleDispatch dispatch;
    dispatch.Initialize = ModuleInitialize;
    dispatch.Start = ModuleStart;
    dispatch.Main = ModuleMain;
    return dispatch;
}