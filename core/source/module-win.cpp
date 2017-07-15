
#include <assert.h>
#include <filesystem>
#include <windows.h>

#include "module.h"
#include "modular.h"

namespace fs = std::experimental::filesystem;

typedef struct _ModuleOsHandle {
    HANDLE win_handle;
} ModuleOsHandle;

Module::Module(const fs::path& _module_path) : module_path(_module_path), status(ModuleDiscovered) {
    oshandle.win_handle = LoadLibrary(module_path.c_str());

    if (oshandle.win_handle == INAVLID_HANDLE_VALUE) {
        status = ErrorNotFound;
        return;
    }
    
    ModuleLoadFunc ModuleLoad = (ModuleLoadFunc) GetProcAddress(oshandle.win_handle, "ModuleLoad");

    if (ModuleLoad == nullptr) {
        status = ErrorNoLoaderFunction;
        FreeLibrary(oshandle.win_handle);
        return;
    }

    dispatch = ModuleLoad();

    status = ModuleLoaded;
}

Module::~Module() {
    if (oshandle.win_handle != INAVLID_HANDLE_VALUE) {
        FreeLibrary(oshandle.win_handle);
    }

    loaded = false;
}