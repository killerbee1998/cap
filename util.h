#include <string>
#include <fstream>
#include <unistd.h>
#include <time.h>

#ifndef UTIL
#define UTIL

class util{
  
 public :
  
  bool project_present(std::string project_name);
  void write_current_time(std::string file_path);
  void write_log(std::string file_path, std::string log);
  void write_local_log(std::string project_name, std::string name, std::string log);
  void write_global_log(std::string project_name, std::string log);
  void replace_line(std::string path, std::string line, std::string replace);
  bool line_present(std::string path, std::string match_line);
  
};


#endif
