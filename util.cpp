#include "util.h"

bool util::project_present(std::string project_name){

  bool present = false;

  std::ifstream project_file_in("projects.txt", std::ios::in);
  std::string line;
  std::string project_path = "/home/" + std::string(getenv("USER")) + "/Documents/" + project_name;
  
  while(std::getline(project_file_in, line)){
    if(line == project_path){
      present = true;
    }
  }

  project_file_in.close();

  return present;
}

void util::write_current_time(std::string file_path){

  std::ofstream file_out(file_path, std::ios::out | std::ios::app);

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  file_out << tm.tm_mday << "/";
  file_out << tm.tm_mon + 1 << "/";
  file_out << tm.tm_year + 1900  << std::endl;

  file_out.close();

}

void util::write_log(std::string file_path, std::string log){

  std::ofstream file_out(file_path, std::ios::out | std::ios::app);
  
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  file_out << "current:  " << tm.tm_mday << "/";
  file_out << tm.tm_mon + 1 << "/";
  file_out << tm.tm_year + 1900 << " : ";

  file_out << log << std::endl;

  file_out.close();

}

void util::write_local_log(std::string project_name, std::string name, std::string log){

  std::string project_path = "/home/" + std::string(getenv("USER")) + "/Documents/" + project_name;

  std::string global_log_path = project_path + "/global_log.txt";
  std::string local_log_path = project_path + "/current/" + name + "/log.txt";

  write_log(global_log_path, name + " " + log);
  write_log(local_log_path, log);
  
}

void util::write_global_log(std::string project_name, std::string log){

  std::string project_path = "/home/" + std::string(getenv("USER")) + "/Documents/" + project_name;

  std::string global_log_path = project_path + "/global_log.txt";

  write_log(global_log_path, log);

}

void util::replace_line(std::string path, std::string init_line, std::string replace){

  std::ifstream file_in(path, std::ios::in);
  std::string line, store = "";
  while(std::getline(file_in, line)){
    if(line != init_line){
      store += line + "\n";
    }else{
      store += replace + "\n";
    }
  }
  file_in.close();
  
  std::ofstream file_out(path, std::ios::out | std::ios::trunc);
  file_out << store;
  file_out.close();
}

bool util::line_present(std::string path, std::string match_line){

  bool present = false;
  
  std::ifstream file_in(path, std::ios::in);
  std::string line;
  while(std::getline(file_in, line)){
    if(line == match_line){
      present = true;
    }
  }

  return present;
}
