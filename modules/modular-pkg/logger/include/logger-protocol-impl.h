
#ifndef __LOGGER_PROTOCOL_IMPL__
#define __LOGGER_PROTOCOL_IMPL__

#include <iostream>
#include <string>

#include "protocol.h"
#include "logger-protocol.h"

class LoggerProtocolImpl : public LoggerProtocol {
public:
    LoggerProtocolImpl() : LoggerProtocol(0) { }

    virtual void Log(std::string msg);
};

#endif