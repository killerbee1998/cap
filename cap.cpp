#include <iostream>
#include <string>
#include <vector>
#include "cmd_handler.h"

int main(int argc, char* argv[]){

  cmd_handler handler;
  std::string cmd;
  std::vector<std::string> args;
   
  
  if(argc > 1){
    cmd = argv[1];
    
    for(int i=2;i<argc;++i){
      args.push_back(argv[i]);
    }

  }

  switch(argc){

  case 1:
    std::cout << "Please issue command" << std::endl;
    std::cout << "No command is currently isssued" << std::endl;
    break;

  case 2:
    handler.zero_arg(cmd);
    break;

  case 3:
    handler.one_arg(cmd, args[0]);
    break;

  default:
    std::cout << "ERROR, Cannot execute cap" << std::endl;

  }
}
    
