
#ifndef __MODULE_SERVICES_IMPL__
#define __MODULE_SERVICES_IMPL__

#include <iostream>
#include <memory>
#include <unordered_map>

#include "protocol.h"
#include "module-services.h"

typedef std::vector<std::shared_ptr<Protocol>> ProtocolSet;

class ModuleServicesImpl : public ModuleServices {
private:
    std::unordered_map<std::string, ProtocolSet> protocols;
    std::shared_ptr<Protocol> prot;

public:
    ModuleServicesImpl() : ModuleServices(), protocols() { }

    virtual void InstallProtocol(const std::shared_ptr<Protocol>& protocol) {
        prot = protocol;
        // if (protocols.count(protocol->Type()) == 0) {
        //     protocols[protocol->Type()] = ProtocolSet();
        // }

        // protocols[protocol->Type()].push_back(protocol);
    }

    virtual const std::shared_ptr<Protocol>& LookupProtocol(const std::string& type) {
        // TODO: Error checking
        // return protocols[type][0];
        return prot;
    }
};

#endif