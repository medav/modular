#include <iostream>
#include <cassert>

#include "module-manager.h"
#include "module-services-impl.h"

int main(int argc, char * argv[]) {
    assert(argc > 1);

    int return_value = 0;

    ModuleManager modman;

    {
        ModuleServicesImpl services;

        modman.DiscoverAndLoad();
        modman.InitAll(services);
        modman.StartAll();

        return_value = modman.ModuleMain(argv[1], argc - 2, argv + 2);
    }
    
    return return_value;
}