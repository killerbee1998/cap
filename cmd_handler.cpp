#include "cmd_handler.h"

void cmd_handler::zero_arg(std::string cmd){

  zero_list zero;

  if(cmd == "help"){
    zero.help();

  }else{
    std::cout << "Invalid command" << std::endl;
  }

}

void cmd_handler::one_arg(std::string cmd, std::string arg_one){

  one_list one;

  if(cmd == "init"){
    if(!one.init(arg_one)){
      std::cout << "cap failed to initialize" << std::endl;
    }

  }else if(cmd == "login"){
    
    if(one.login(arg_one)){
      std::cout << "Sucessfully logged in" << std::endl;
      
    }else{
      std::cout << "Login Unsuccessful" <<std::endl;
    }
    
  }else if(cmd == "logout"){

    if(one.logout(arg_one)){
      std::cout << "Sucessfully logged off" <<std::endl;

    }else{
      std::cout << "Logoff Unsuccessful" << std::endl;
    }
    
  }else{
    std::cout << "Invalid command" << std::endl;
  }
}
