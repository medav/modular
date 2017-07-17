
#ifndef __LOGGER_PROTOCOL__
#define __LOGGER_PROTOCOL__

#include <iostream>
#include <string>

#include "protocol.h"

class LoggerProtocol : public Protocol {
public:
    LoggerProtocol(unsigned int _version) : Protocol("logger", _version) { }

    virtual void Log(std::string msg) = 0;
};

#endif