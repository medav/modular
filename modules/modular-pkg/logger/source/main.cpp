
#include <iostream>
#include <memory>

#include "modular.h"
#include "module-interface.h"
#include "logger-protocol.h"
#include "logger-protocol-impl.h"

ModuleServices * services;
std::unique_ptr<LoggerProtocolImpl> logger_prot;

void ModuleInitialize(ModuleServices * _services) {
    services = _services;
    logger_prot.reset(new LoggerProtocolImpl);
    services->InstallProtocol((Protocol *) logger_prot.get());
}

void ModuleStart() {
    logger_prot->Log("Logger module started");
}

EXPORT ModuleDispatch ModuleLoad() {
    ModuleDispatch dispatch;
    dispatch.Initialize = ModuleInitialize;
    dispatch.Start = ModuleStart;
    dispatch.Main = nullptr;
    return dispatch;
}