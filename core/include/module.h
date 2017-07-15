
#ifndef __MODULE__
#define __MODULE__

#include <filesystem>

#include "module-dispatch.h"

namespace fs = std::experimental::filesystem;

struct ModuleOsHandle;

class Module {
private:
    struct ModuleOsHandle oshandle;
    bool loaded;

    ModuleDispatch dispatch;

public:
    Module() = delete;
    Module(const fs::path&);
    Module(const Module& other) = delete;
    Module(Module&& other);

    void operator=(const Module& other) = delete;
    void operator=(Module&& other);

    const ModuleDispatch& Dispatch() const { return dispatch; }

};

#endif