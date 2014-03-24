#ifndef NIBBLEREXCEPTION_HH
#define NIBBLEREXCEPTION_HH

#include "Nibbler.hh"

class   NibblerException : public std::exception
{
private:
    const std::string       _error;
public:
    NibblerException(const std::string &error);
    ~NibblerException(void) throw() {}
    const std::string           &getError(void) const;
    virtual const std::string   getMessage(void) const;
};

#endif // NIBBLEREXCEPTION_HH
