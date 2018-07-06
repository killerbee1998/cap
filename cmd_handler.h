#include <string>
#include <iostream>
#include <fstream>

#include "zero_list.h"
#include "one_list.h"

#ifndef  HANDLE
#define HANDLE


class cmd_handler{

 public:

  void zero_arg(std::string cmd);

  void one_arg(std::string cmd, std::string arg_one);

};

#endif
