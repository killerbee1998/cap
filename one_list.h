#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>

#ifndef ONE_LIST
#define ONE_LIST

class one_list{

 public:

  bool init(std::string path);

};
#endif
