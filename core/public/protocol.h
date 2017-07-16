
#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <string>

class Protocol {
protected:
    std::string name;
    unsigned int version;

public:
    Protocol() = delete;
    Protocol(const std::string& _name, unsigned int _version) : name(_name), version(_version) { }
    Protocol(const Protocol& other) = delete;
    Protocol(Protocol&& other) = delete;
    void operator=(const Protocol& other) = delete;
    void operator=(Protocol&& other) = delete;

    virtual const std::string& Name() { return name; }
    virtual unsigned int Version() { return version; }

    virtual ~Protocol() { }
};

#endif