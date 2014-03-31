#ifndef NIBBLEREXCEPTION_HH
#define NIBBLEREXCEPTION_HH

#include "Nibbler.hh"

class   NibblerException : public std::exception
{
protected:
    const std::string       _module;
public:
    NibblerException(const std::string &module) : _module(module) {}
    ~NibblerException(void) throw() {}
    virtual const std::string   getMessage(void) const = 0;
};

#endif // NIBBLEREXCEPTION_HH
