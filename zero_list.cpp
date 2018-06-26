#include "zero_list.h"

void zero_list::help(){

  std:: ifstream help_file("help.md");
  std::string content;

  if(help_file.is_open()){

    while (!help_file.eof()){
      std::getline(help_file, content);
      std::cout << content << std::endl;
    }
  }
}
