
#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <iostream>
#include <string>

class Protocol {
private:
    std::string type;

public:
    Protocol() = delete;
    Protocol(const std::string& _type) : type(_type) { }
    Protocol(const Protocol& other) = delete;
    Protocol(Protocol&& other) = delete;
    void operator=(const Protocol& other) = delete;
    void operator=(Protocol&& other) = delete;

    const std::string& Type() { return type; }

    virtual ~Protocol() { }
};

#endif