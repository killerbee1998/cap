#include "handler.h"

handler::handler(){

  table["help"] = [](args a) { //zero func
    return zero::help();
  };
  
  table["c-def"] = [](args a){
    return zero::c_def();
  };

  table["init"] = [](args a) { //one func
    return one::init(a[0]);
  };

  table["login"] = [](args a) {
    return one::login(a[0]);
  };

  table["logout"] = [](args a) {
    return one::logout(a[0]);
  };

  table["destroy"] = [](args a) {
    return one::destroy(a[0]);
  };

  table["explore"] = [](args a) {
    return one::explore(a[0]);
  };
  
  table["cd"] = [](args a) {
    return one::cd(a[0]);
  };
  table["add"] = [](args a) { //two func
    return two::add(a[0], a[1]);
  };

  table["sub"] = [](args a) {
    return two::sub(a[0], a[1]);
  };

  table["add-dir"] = [](args a) {
    return two::add_dir(a[0], a[1]);
  };

  table["sub-dir"] = [](args a) {
    return two::sub_dir(a[0], a[1]);
  };

  table["add-new"] = [](args a) {
    return two::add_new(a[0], a[1]);
  };

}

void handler::handle(std::string cmd, args a){

  if(table.count(cmd) == 1){

    if(table[cmd](a)){
      std::cout << cmd << " Operation Successful" << std::endl;
      
    }else{
      std::cout << cmd << " Operation Failed" << std::endl;
    }

  }else{

    std::cout << "Command not present. Type cap help for a list of commands" <<std::endl;

  }

}
