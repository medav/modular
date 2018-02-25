
#ifndef __LOGGER_PROTOCOL__
#define __LOGGER_PROTOCOL__

#include <iostream>
#include <string>

#include "core/public/protocol.h"

class LoggerProtocol : public Protocol {
public:
    LoggerProtocol() : Protocol("logger") { }

    virtual void Log(std::string msg) = 0;
};

#endif