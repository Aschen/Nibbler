#ifndef DLLLOADER_HH_
# define DLLLOADER_HH_

#include <string>
#include <iostream>
#include <dlfcn.h>

/*
 * DLLoader
 * Charge une librairie dynamique
 * T : type de la classe renvoyer
 * F : prototype de la fonction renvoyant une instance de la classe
 */

template <typename T, typename F>
class	DLLoader
{
private:
  const std::string	_dl;
  void			*_dlHandler;
public:
  DLLoader(const std::string &dl)
  {
    if ((_dlHandler = dlopen(dl.c_str(), RTLD_LAZY)) == NULL)
      std::cerr << dlerror() << std::endl;
  }

  ~DLLoader(void)
  {
    if (_dlHandler != NULL)
      dlclose(_dlHandler);
  }

  T	*getInstance(const std::string &entry_point)
  {
    F	create;

    if (_dlHandler == NULL)
      {
	std::cerr << "No library loaded !" << std::endl;
	return NULL;
      }
    if ((create = reinterpret_cast<F>(dlsym(_dlHandler, entry_point.c_str()))) == NULL)
      {
	std::cerr << dlerror() << std::endl;
	return NULL;
      }
    return create("Test");
  }
};

#endif /* !_DLLLOADER_HH_ */
