#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "handler.h"

int main(int argc, char* argv[]){

  if(argc < 2){
    std::cout << "Enter a command" << std::endl;
    std::cout << "Type cap help for a list of commands" << std::endl;
    return 0;

  }
  std::string cmd = argv[1];
  std::vector<std::string> args;

  if(argc < 3){
    args.push_back("NO_ARG");

  }else{

    for(int i = 2; i < argc; ++i){
      args.push_back(argv[i]);
    }

  }
  
  handler handler;

  handler.handle(cmd, args);
  
}
