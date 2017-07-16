
#ifndef __MODULE_SERVICES__
#define __MODULE_SERVICES__

#include <memory>
#include <unordered_map>

#include "protocol.h"

class ModuleServices {
private:
    std::unordered_map<std::string, Protocol *> protocols;

public:
    ModuleServices() : protocols() { }
    ModuleServices(const ModuleServices& other) = delete;
    ModuleServices(ModuleServices&& other) = delete;
    void operator=(const ModuleServices& other) = delete;
    void operator=(ModuleServices&& other) = delete;

    void InstallProtocol(Protocol * protocol) {
        protocols[protocol->Name()] = protocol;
    }

    Protocol * LookupProtocol(const std::string& name) {
        return protocols[name];
    }
};

#endif