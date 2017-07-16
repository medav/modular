
#include <cassert>
#include <filesystem>
#include <iostream>
#include <vector>

#include "module-manager.h"

namespace fs = std::experimental::filesystem;

bool ShouldSearch(const fs::path& dirpath) {
    if (dirpath.stem().string() == "include") return false;
    if (dirpath.stem().string() == "public") return false;
    if (dirpath.stem().string() == "source") return false;
    if (dirpath.stem().string() == "obj") return false;
    return true;
}

void ModuleManager::DiscoverAndLoadRecursive(const fs::path& root) {
    for (const auto& entry : fs::directory_iterator(root)) {
        if (fs::is_directory(entry.path())) {
            if (ShouldSearch(entry.path())) {
                DiscoverAndLoadRecursive(entry.path());
            }
        }
        else if (fs::is_regular_file(entry.path())) {
            if (entry.path().extension().string() == ".dll") {
                std::cout << "Loading " << entry.path().filename() << std::endl;
                modules.push_back(Module(entry.path()));
            }
        }
    }
}

void ModuleManager::DiscoverAndLoad() {
    DiscoverAndLoadRecursive(fs::path("modules"));
}

void ModuleManager::InitAll() {
    std::cout << "Init" << std::endl;
    for (Module& module :  modules) {
        if (module.Status() == ModuleLoaded)
            module.Dispatch().Initialize();
    }
}

void ModuleManager::StartAll() {
    std::cout << "Start" << std::endl;
    for (Module& module :  modules) {
        if (module.Status() == ModuleLoaded)
            module.Dispatch().Start();
    }
}

int ModuleManager::ModuleMain(const std::string& module_name, int argc, char * argv[]) {
    auto& it = std::find_if(modules.begin(), modules.end(), [&](Module& module) -> bool {
        return module.Name() == module_name;
    });

    assert(it != modules.end());
    Module& start_module = *it;
    assert(start_module.Dispatch().Main != nullptr);

    return start_module.Dispatch().Main(argc, argv);
}

ModuleManager::~ModuleManager() {

}