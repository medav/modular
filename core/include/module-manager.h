
#ifndef __MODULE_MANAGER__
#define __MODULE_MANAGER__

#include <vector>
#include <filesystem>

#include "module.h"
#include "module-services-impl.h"

namespace fs = std::experimental::filesystem;

class ModuleManager {
private:
    std::vector<Module> modules;

    void DiscoverAndLoadRecursive(const fs::path& root);

public:
    ModuleManager() = default;
    ModuleManager(const ModuleManager& other) = delete;
    ModuleManager(ModuleManager&& other) = delete;

    void operator=(const ModuleManager& other) = delete;
    void operator=(ModuleManager&& other) = delete;

    void DiscoverAndLoad();
    void InitAll(ModuleServices& services);
    void StartAll();
    int ModuleMain(const std::string& module_name, int argc, char * argv[]);

    const auto begin() const { return modules.begin(); }
    const auto end() const { return modules.end(); }

    ~ModuleManager();
};

#endif