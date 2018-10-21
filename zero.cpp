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

bool zero::c_def(){

  bool success = false;
  std::string default_type;
  
  std::cout << "What default would you like to change?" << std::endl;
  std::cout << "1. To change the default path type path \n";
  std::cout << "2. To change the default editor type editor \n";
  std::cin >> default_type;
  
  std::string default_f_p = util::get_cap_path() + "/config/default_" + default_type + ".txt";
  std::string default_p_p;
  
  std::ifstream default_f_in (default_f_p, std::ios::in);
  if(default_f_in.is_open()){ //if default file is present
    default_f_in >> default_p_p;
    default_f_in.close();
    
    std::string response;
    std::cout << "The current default is " << default_p_p << std::endl;
    std::cout << "Would you like to change the default?" <<std::endl;
    std::cout << "Press y to say yes" << std::endl;
    std::cin >> response;

    if(response == "y" || response == "Y"){
      std::string new_default_p_p;
      std::cout << "Enter the new default name here:" << std::endl;
      std::cin >> new_default_p_p;

      std::ofstream default_f_out(default_f_p, std::ios::out | std::ios::trunc);
      default_f_out << new_default_p_p;
      default_f_out.close();

      success = true;
      
    }else{

      std::cout << "Default not changed" << std::endl;
      
    }

  }else{
    std::cout << "Cant open default file at " << default_f_p <<std::endl;

  }

  return success;

}
