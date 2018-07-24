#include "zero.h"

bool zero::help(){

  bool success = true;
  
  std::string help_path = "/home/" + std::string(getenv("USER")) + "/Documents/cap/docs/help.md";
  std::ifstream help_f(help_path, std::ios::in);
  std::string line;

  if(!help_f.is_open()){
    success = false;

  }else{
    while(std::getline(help_f, line)){
      std::cout << line << std::endl;
    }
  }

  return success;
}
