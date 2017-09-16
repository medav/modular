
#ifndef __MODULAR_DEBUG__
#define __MODULAR_DEBUG__

#include <iostream>
#include <exception>
#include <string>
#include <sstream>

class ModularAssertFailure : public std::runtime_error {
public:
    std::string file;
    std::string function;
    uint64_t line;
    std::string assert_text;
    std::string full_text;

    ModularAssertFailure(
        const char * _file,
        const char * _function, 
        uint64_t _line, 
        const char * _assert_text)
        : std::runtime_error("Assertion Failure"),
          file(_file),
          function(_function), 
          line(_line), 
          assert_text(_assert_text) { 

        std::stringstream ss;
        ss << "[" << "Line" << ":" << line << "][" << function << "] Assertion: (" 
            << assert_text << ")"; 

        full_text = ss.str();
    }

    const char * what() const throw () {
        return full_text.c_str();
    }
};

#define ASSERT(x)                                                          \
    if (!(x)) {                                                            \
        throw ModularAssertFailure(__FILE__, __FUNCTION__, __LINE__, # x); \
    }


#endif