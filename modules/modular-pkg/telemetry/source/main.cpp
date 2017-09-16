
#include <iostream>
#include <memory>

#include "modular.h"
#include "module-interface.h"
#include "logger-protocol.h"
#include "logger.h"

ModuleServices * services;
std::shared_ptr<LoggerProtocol> logger_prot;

void ModuleInitialize(ModuleServices& _services) {
    services = &_services;
    services->InstallProtocol(std::make_shared<LoggerProtocolImpl>());
}

void ModuleStart() {
    logger_prot = std::dynamic_pointer_cast<LoggerProtocol>(services->LookupProtocol("logger"));
    logger_prot->Log("Logger module started.");
}

EXPORT ModuleDispatch ModuleLoad() {
    ModuleDispatch dispatch;
    dispatch.Initialize = ModuleInitialize;
    dispatch.Start = ModuleStart;
    dispatch.Main = nullptr;
    return dispatch;
}