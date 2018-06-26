#include "one_list.h"

bool one_list::init(std::string path){

  bool success = true;
  path = "/home/" + path;
  struct stat st ={0};

  if(stat(path.c_str(), &st) == -1){
    mkdir(path.c_str(), 0700);

  }else{
    success = false;
  }

  return success;
}
