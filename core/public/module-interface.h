
#ifndef __MODULE_DISPATCH__
#define __MODULE_DISPATCH__

#include "modular.h"

typedef struct {
    REQUIRED void (*Initialize)();
    REQUIRED void (*Start)();
    OPTIONAL void (*Main)(IN int argc, IN char * argv[]);
} ModuleDispatch;

typedef ModuleDispatch (*ModuleLoadFunc)();

#endif