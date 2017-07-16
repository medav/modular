
#include <iostream>

#include "modular.h"
#include "module-interface.h"

void ModuleInitialize() {
    std::cout << "ModuleInitialize  " << std::endl;
}

void ModuleStart() {
    std::cout << "ModuleStart" << std::endl;
}

int ModuleMain(int argc, char * argv[]) {
    std::cout << "Hello, Modular!" << std::endl;
    return 0;
}


EXPORT ModuleDispatch ModuleLoad() {
    std::cout << "ModuleLoad" << std::endl;
    ModuleDispatch dispatch;
    dispatch.Initialize = ModuleInitialize;
    dispatch.Start = ModuleStart;
    dispatch.Main = ModuleMain;
    return dispatch;
}