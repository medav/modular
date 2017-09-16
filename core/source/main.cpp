#include <iostream>

#include "modular-debug.h"
#include "module-manager.h"
#include "module-services-impl.h"

int main(int argc, char * argv[]) {
    int return_value = 0;
    ModuleManager modman;

    try {
        
        {
            ModuleServicesImpl services;

            modman.DiscoverAndLoad();
            modman.InitAll(services);
            modman.StartAll();

            if (argc < 2) {
                return_value = -1;

                std::cout << "---- Available Startup Modules ----" << std::endl;
                for (const auto& module : modman) {
                    if (module.IsStartupModule()) {
                        std::cout << module.Name() << std::endl;
                    }
                }
            }
            else {
                return_value = modman.ModuleMain(argv[1], argc - 1, argv + 1);
            }
        }
    }
    catch (ModularAssertFailure& exception) {
        std::cerr << "Fatal Error!" << std::endl << exception.what() << std::endl;
    }

    return return_value;
}