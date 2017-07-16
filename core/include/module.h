
#ifndef __MODULE__
#define __MODULE__

#include <filesystem>
#include <memory>

#include "module-interface.h"

namespace fs = std::experimental::filesystem;

struct _ModuleOsHandle;

typedef enum {
    ModuleDiscovered,
    ModuleLoaded,
    ModuleStarted,

    // Error codes
    ErrorNotFound,
    ErrorNoLoaderFunction,
    ErrorDispatchFailed

} ModuleStatus;

class Module {
private:
    fs::path module_path;
    std::unique_ptr<struct _ModuleOsHandle> oshandle;
    ModuleDispatch dispatch;
    ModuleStatus status;
    std::string name;

public:
    Module() = delete;
    Module(const fs::path&);
    Module(const Module& other) = delete;
    Module(Module&& other);

    void operator=(const Module& other) = delete;
    void operator=(Module&& other);

    ModuleStatus Status() const { return status; }
    const std::string& Name() const { return name; }

    const ModuleDispatch& Dispatch() const { return dispatch; }

    ~Module();
};

#endif