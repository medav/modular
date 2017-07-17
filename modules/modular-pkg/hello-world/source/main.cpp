
#include <iostream>
#include <memory>

#include "modular.h"
#include "module-interface.h"
#include "logger-protocol.h"

ModuleServices * services;
LoggerProtocol * logger;

void ModuleInitialize(ModuleServices * _services) {
    services = _services;
}

void ModuleStart() {
    logger = static_cast<LoggerProtocol *>(services->LookupProtocol("logger"));
}

int ModuleMain(int argc, char * argv[]) {
    logger->Log("Hello, Modular!");
    return 0;
}


EXPORT ModuleDispatch ModuleLoad() {
    ModuleDispatch dispatch;
    dispatch.Initialize = ModuleInitialize;
    dispatch.Start = ModuleStart;
    dispatch.Main = ModuleMain;
    return dispatch;
}