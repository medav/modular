
#ifndef __MODULE_MANAGER__
#define __MODULE_MANAGER__

#include <vector>
#include <filesystem>

#include "module.h"
#include "module-services.h"

namespace fs = std::experimental::filesystem;

class ModuleManager {
private:
    ModuleServices& services;
    std::vector<Module> modules;

    void DiscoverAndLoadRecursive(const fs::path& root);

public:
    ModuleManager() = delete;
    ModuleManager(ModuleServices& _services) : services(_services) { }

    ModuleManager(const ModuleManager& other) = delete;
    ModuleManager(ModuleManager&& other) = delete;

    void operator=(const ModuleManager& other) = delete;
    void operator=(ModuleManager&& other) = delete;

    void DiscoverAndLoad();
    void InitAll();
    void StartAll();
    int ModuleMain(const std::string& module_name, int argc, char * argv[]);

    ~ModuleManager();
};

#endif