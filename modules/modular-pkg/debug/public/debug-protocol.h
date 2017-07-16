
#ifndef __DEBUG_PROTOCOL__
#define __DEBUG_PROTOCOL__

#include <iostream>
#include <string>

#include "protocol.h"

class DebugProtocol : public Protocol {
public:
    DebugProtocol() : Protocol("debug", 0) { }

    void Debug(std::string msg) {
        std::cout << "[Debug] " << msg << std::endl;
    }
};

#endif