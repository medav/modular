
#ifndef __MODULE_MANAGER__
#define __MODULE_MANAGER__

#include "module.h"
#include "module-services.h"

class ModuleManager {
private:
    ModuleServices& services;
    std::vector<Module> modules;

public:
    ModuleManager() = delete;
    ModuleManager(ModuleServices& _services) : services(_services) { }

    ModuleManager(const ModuleManager& other) = delete;
    ModuleManager(ModuleManager&& other) = delete;

    void operator=(const ModuleManager& other) = delete;
    void operator=(ModuleManager&& other) = delete;

    void DiscoverAndLoad();
    void Init();
    int StartModule(int argc, char * argv[]);

    ~ModuleManager();
};

#endif