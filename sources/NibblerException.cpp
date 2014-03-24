#include "NibblerException.hh"

NibblerException::NibblerException(const std::string &error) : _error(error)
{
}

const std::string &NibblerException::getError() const
{
    return _error;
}

const std::string NibblerException::getMessage() const
{
    std::stringstream   ss;

    ss << "Error : " << _error;
    return ss.str();
