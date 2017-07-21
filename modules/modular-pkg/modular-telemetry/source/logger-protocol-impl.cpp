
#include <iostream>
#include <string>

#include "logger-protocol-impl.h"

void LoggerProtocolImpl::Log(std::string msg) {
    std::cout << "[Log] " << msg << std::endl;
}