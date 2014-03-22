//
// NibblerException.cpp for - in /home/brunne_r/Links/nibbler/sources
//
// Made by brunne-r
// Login   <brunne-r@epitech.net>
//
// Started on  Sat Mar 22 16:51:13 2014 brunne-r
// Last update Sat Mar 22 16:56:56 2014 brunne-r
//

#include "NibblerException.hh"

NibblerException::NibblerException(const std::string &error) : _error(error)
{
}

const std::string &NibblerException::getError(void) const
{
  return _error;
}

const std::string NibblerException::getMessage(void) const
{
  return _error;
}
