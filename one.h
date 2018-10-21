#include <stdlib.h>

#include <string>
#include <fstream>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "util.h"

#ifndef ONE
#define ONE


namespace one{

  bool init(std::string project_name);

  bool login(std::string project_name);

  bool logout(std::string project_name);

  bool destroy(std::string project_name);

  bool explore(std::string project_name);

  bool cd(std::string project_name);

}

#endif
