
#include <filesystem>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

#include "module.h"
#include "public/modular.h"

namespace fs = std::experimental::filesystem;

typedef struct _ModuleOsHandle {
    void * module;
} ModuleOsHandle;

Module::Module(const fs::path& _module_path) : module_path(_module_path), status(ModuleDiscovered), name(_module_path.stem().string()), oshandle(new ModuleOsHandle) {
    std::string fullpath = fs::absolute(module_path).string();
    oshandle->module = dlopen((char *)fullpath.c_str(), RTLD_LAZY);

    if (oshandle->module == 0) {
        status = ErrorNotFound;
        return;
    }
    
    ModuleLoadFunc ModuleLoad = (ModuleLoadFunc) dlsym(oshandle->module, "ModuleLoad");

    if (ModuleLoad == nullptr) {
        status = ErrorNoLoaderFunction;
        dlclose(oshandle->module);
        return;
    }

    dispatch = ModuleLoad();

    status = ModuleLoaded;
}

Module::Module(Module&& other) : 
    module_path(std::move(other.module_path)), 
    status(other.status), 
    name(std::move(other.name)), 
    oshandle(std::move(other.oshandle)), 
    dispatch(other.dispatch) {

}

Module::~Module() {
    if (oshandle.get() != nullptr) {
        if (oshandle->module != nullptr) {
            dlclose(oshandle->module);
        }
    }

    status = ModuleDiscovered;
}