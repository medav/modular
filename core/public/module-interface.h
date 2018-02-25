
#ifndef __MODULE_DISPATCH__
#define __MODULE_DISPATCH__

#include <memory>

#include "modular.h"
#include "module-services.h"

typedef struct {
    REQUIRED void (*Initialize)(IN ModuleServices& services);
    REQUIRED void (*Start)();
    OPTIONAL int (*Main)(IN int argc, IN char * argv[]);
} ModuleDispatch;

using ModuleLoadFunc = ModuleDispatch(*)(void);

#endif