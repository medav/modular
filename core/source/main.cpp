#include <iostream>
#include <cassert>

#include "module-manager.h"
#include "module-services.h"

int main(int argc, char * argv[]) {
    assert(argc > 1);

    ModuleServices services;
    ModuleManager modman(services);

    modman.DiscoverAndLoad();
    modman.InitAll();
    modman.StartAll();
    return modman.ModuleMain(argv[1], argc - 2, argv + 2);
}