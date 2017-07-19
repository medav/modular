
#ifndef __MODULE_SERVICES__
#define __MODULE_SERVICES__

#include <iostream>
#include <memory>
#include <unordered_map>

#include "protocol.h"

class ModuleServices {
public:
    ModuleServices() { }
    ModuleServices(const ModuleServices& other) = delete;
    ModuleServices(ModuleServices&& other) = delete;
    void operator=(const ModuleServices& other) = delete;
    void operator=(ModuleServices&& other) = delete;

    virtual void InstallProtocol(const std::shared_ptr<Protocol>& protocol) = 0;
    virtual const std::shared_ptr<Protocol>& LookupProtocol(const std::string& name) = 0;
};

#endif