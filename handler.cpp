#include "handler.h"

handler::handler(){

  table["help"] = [](args a) {
    return zero::help();
  };

  table["init"] = [](args a) {
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

  table["add"] = [](args a) {
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


}

void handler::handle(std::string cmd, args a){

  if(table[cmd](a)){
    std::cout << cmd << " Operation Successful" << std::endl;

  }else{
    std::cout << cmd << " Operation Failed" << std::endl;
  }

}
