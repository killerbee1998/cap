#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#ifndef ONE_LIST
#define ONE_LIST

class one_list{

 public:

  bool init(std::string project_name);

};
#endif
