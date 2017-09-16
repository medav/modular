
#include <iostream>
#include <string>

#include "logger.h"

void LoggerProtocolImpl::Log(std::string msg) {
    std::cout << "[Log] " << msg << std::endl;
}