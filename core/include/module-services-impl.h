
#ifndef __MODULE_SERVICES_IMPL__
#define __MODULE_SERVICES_IMPL__

#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>

#include "protocol.h"
#include "modular-debug.h"
#include "module-services.h"

typedef std::vector<std::shared_ptr<Protocol>> ProtocolSet;

class ModuleServicesImpl : public ModuleServices {
private:
    std::unordered_map<std::string, ProtocolSet> protocols;
    std::shared_ptr<Protocol> null_protocol;

public:
    ModuleServicesImpl() : 
        ModuleServices(), protocols(), null_protocol(nullptr) { }

    virtual void InstallProtocol(const std::shared_ptr<Protocol>& protocol) {

        std::cout << protocol->Type() << std::endl;
        if (protocols.count(protocol->Type()) == 0) {
            protocols[protocol->Type()] = ProtocolSet();
        }

        protocols[protocol->Type()].push_back(protocol);
    }

    virtual const std::shared_ptr<Protocol>& LookupProtocol(
        const std::string& type) {

        ASSERT(protocols.find(type) != protocols.end());

        auto& protocol_set = protocols[type];
        ASSERT(protocol_set.size() > 0);

        return protocol_set[0];
    }

    virtual const std::shared_ptr<Protocol>& LookupProtocolByFilter(
        const std::string& type, 
        ProtocolFilterFunc ProtocolFilter) {

        ASSERT(protocols.find(type) != protocols.end());
        
        auto& protocol_set = protocols[type];
        
        for (auto& protocol : protocol_set) {
            if (ProtocolFilter(protocol)) {
                return protocol;
            }
        }

        ASSERT(false);

        return null_protocol;
    }
};

#endif