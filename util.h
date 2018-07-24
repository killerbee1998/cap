#include <string>
#include <fstream>
#include <iostream>

#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef UTIL
#define UTIL

namespace util{

  //project genral

  std::string get_project_path(std::string project_name);

  bool is_project_present(std::string project_name);

  //logs

  void write_global_log(std::string project_name, std::string log);

  void write_local_log(std::string project_name, std::string name, std::string log);

  //logins

  bool is_logged(std::string project_name);

  std::string get_logged_name(std::string project_name);

  //time

  std::string get_time();

  std::string get_date();

  //line

  void remove_line(std::string f_p, std::string remove);

  //dir

  bool is_dir_updated(std::string project_name);
  
  void update_dir(std::string project_name);

  //file

  bool is_file_present(std::string path);
} 

#endif
