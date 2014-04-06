#ifndef DLLLOADER_HH_
# define DLLLOADER_HH_

#include <string>
#include <iostream>
#include <dlfcn.h>

#include "NibblerException.hh"

/*
 * DLLoader
 * Charge une librairie dynamique
 * T : type de la classe renvoye
 * F : prototype de la fonction renvoyant une instance de la classe
 */

template <typename T, typename F>
class	DLLoader
{
public:
    class   Error : public NibblerException
    {
    private:
        std::stringstream   _msg;
    public:
        Error(const std::string &error) : NibblerException("DLLoader")
        {
            _msg << error << std::endl;
        }
        Error(const Error &cpy) : NibblerException("DLLoader")
        {
            if (&cpy != this)
            {
                _msg << cpy.getMessage();
            }
        }
        ~Error(void) throw() {}
        const std::string   getMessage(void) const
        {
            return _msg.str();
        }
    };
private:
    const std::string	_dl;
    void                *_dlHandler;
public:
    DLLoader(const std::string &dl)
    {
        if ((_dlHandler = dlopen(dl.c_str(), RTLD_LAZY)) == NULL)
            throw std::runtime_error(dlerror());
    }

    ~DLLoader(void)
    {
        if (_dlHandler != NULL)
            dlclose(_dlHandler);
    }

    T	*getInstance(const std::string &entry_point)
    {
        F	create;

        if ((create = reinterpret_cast<F>(dlsym(_dlHandler, entry_point.c_str()))) == NULL)
            throw std::runtime_error(dlerror());
        return create();
    }
};

#endif /* !_DLLLOADER_HH_ */
