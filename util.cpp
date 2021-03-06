#include "util.h"

//project genral

std::string util::get_project_path(std::string project_name){

  std::string project_list_path = util::get_cap_path() + "/config/project_list.txt";
  std::string project_path = "ERROR";

  std::ifstream project_list_f(project_list_path, std::ios::in);
  std::string line;
  while(std::getline(project_list_f, line)){
    std::string temp, line_name;
    for(int i = line.length()-1; line[i]!='/'; --i){
      temp.push_back(line[i]);
    }
    for(int i = temp.length()-1; i > -1; --i){
      line_name.push_back(temp[i]);
    }
    
    if(line_name == project_name){
      project_path = line;
    }
    
  }

  project_list_f.close();
  return project_path;
  
}

bool util::is_project_present(std::string project_name){
  
  std::string project_list_path = util::get_cap_path() + "/config/project_list.txt";

  bool project_exist = false;

  struct stat st = {0};

  if(stat(project_list_path.c_str(), &st) < 0){
    return project_exist;
  }

  std::ifstream project_list_f(project_list_path, std::ios::in);
  std::string line;
  while(std::getline(project_list_f, line)){
    std::string temp, line_name;
    
    for(int i = line.length()-1; line[i]!='/'; --i){
      temp.push_back(line[i]);
    }
    for(int i = temp.length()-1; i > -1; --i){
      line_name.push_back(temp[i]);
    }
    
    if(line_name == project_name){
      if(util::is_file_present(line)){
	project_exist = true;
      }
    }
    
  }
  
  project_list_f.close();

  return project_exist;
}

std::string util::get_cap_path(){

  std::string path = "/home/" + std::string(getenv("USER")) + "/Documents/cap";
  return path;
}
//logs

void util::write_global_log(std::string project_name, std::string log){

  std::string log_f_p = util::get_project_path(project_name) + "/global_log.txt";

  std::ofstream log_f(log_f_p, std::ios::out | std::ios::app);
  log_f << util::get_time() << ": " << log << std::endl << "\n";
  log_f.close();
}

void util::write_local_log(std::string project_name, std::string name, std::string log){

  std::string global_log_f_p = util::get_project_path(project_name) + "/global_log.txt";
  std::string local_log_f_p = util::get_project_path(project_name) + "/current/" + name + "/log.txt";

  std::ofstream global_log_f(global_log_f_p, std::ios::out | std::ios::app);
  global_log_f << util::get_time() << ": " << name << " " << log << std::endl <<"\n";
  global_log_f.close();

  std::ofstream local_log_f(local_log_f_p, std::ios::out | std::ios::app);
  local_log_f << util::get_time() << ": " << name << " " << log << std::endl<<"\n";
  local_log_f.close();
}

//logins

bool util::is_logged(std::string project_name){

  bool logged = false;

  std::string login_f_p = util::get_project_path(project_name) + "/config/login.txt";

  std::ifstream login_f_in(login_f_p, std::ios::in);
  if(login_f_in.is_open()){
    std::string line, log_stat;
    login_f_in >> line;

    int begin = 1;
    for(unsigned int i = 0; line[i]!='*'; ++i){
      ++begin;
    }

    for(unsigned int i = begin; i < line.length(); ++i){
      log_stat.push_back(line[i]);
    }

    if(log_stat == "logged"){
      logged = true;
    }
    
  }

  login_f_in.close();
    

  return logged;
}

std::string util::get_logged_name(std::string project_name){

  std::string name = "ERROR";
  
  std::string login_f_p = util::get_project_path(project_name) + "/config/login.txt";

  struct stat st = {0};

  if(stat(login_f_p.c_str(), &st) == 0){
    std::ifstream login_f_in(login_f_p, std::ios::in);
    std::string line;
    name = "";
    login_f_in >> line;
    for(int i = 0; line[i] != '*'; ++i){
      name.push_back(line[i]);
    }
    
    login_f_in.close();

  }  

  return name;

}

//time

std::string util::get_time(){

  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  return std::string(asctime(tm));

}

std::string util::get_date(){

  time_t t = time(NULL);
  struct tm *tm = localtime(&t);

  std::string date = std::to_string(tm->tm_mday);
  std::string mon = std::to_string(tm->tm_mon + 1);
  std::string yr = std::to_string(tm->tm_year + 1900);

  return std::string(yr + ":" + mon + ":" + date);

}

//dir

bool util::is_dir_updated(std::string project_name){

  bool updated = false;

  std::string date_f_p = util::get_project_path(project_name) + "/config/date.txt";

  std::ifstream date_f_in(date_f_p, std::ios::in);
  std::string line;
  date_f_in >> line;
  date_f_in.close();

  if(line == util::get_date()){
    updated = true;
  }

  return updated;

}

void util::update_dir(std::string project_name){

  if(!util::is_dir_updated(project_name)){
    std::string date_f_p = util::get_project_path(project_name) + "/config/date.txt";

    std::ifstream date_f_in(date_f_p, std::ios::in);
    std::string date;
    date_f_in >> date;
    date_f_in.close();
    
    std::string cd = "cd " + util::get_project_path(project_name);
    std::string cp = "cp -r current " + date;

    system(std::string(cd+ " && " + cp).c_str());
    
    std::ofstream date_f_out(date_f_p, std::ios::out | std::ios::trunc);
    date_f_out << util::get_date();
    date_f_out.close();
  }

}

std::vector<std::string> util::return_dir(const std::string &pattern){
  glob_t glob_r;
  glob(pattern.c_str(),GLOB_TILDE,NULL, &glob_r);
  std::vector<std::string> files;
  for(unsigned int i = 0; i<glob_r.gl_pathc;++i){
    files.push_back(std::string(glob_r.gl_pathv[i]));
  }
  globfree(&glob_r);
  return files;
}

void util::show_dir(std::string dir_name){
  std::vector<std::string> f = util::return_dir("./*");
  for(unsigned int i=0;i<f.size();++i){
    std::cout << f[i] << std::endl;
  }
}

//file

bool util::is_file_present(std::string path){

  bool present = false;
  struct stat st = {0};

  if(stat(path.c_str(), &st) == 0){
    present = true;
  }

  return present;

}

//line

void util::remove_line(std::string f_p, std::string remove){

  std::ifstream f_in(f_p, std::ios::in);
  std::string line, store = "";
  while(std::getline(f_in, line)){
    if(line != remove){
      store += line + "\n";
    }
  }
  f_in.close();

  std::ofstream f_out(f_p, std::ios::out | std::ios::trunc);
  f_out << store;

  f_out.close();

}


//encryption

std::string util::encrypt(std::string str){

  int sum = 0;
  
  for(unsigned int i = 0; i < str.length(); ++i){
    sum += str[i];
  }

  int key = sum * str.length();
  int key_store = key;
  std::string encr_str;
  
  for(unsigned int i=0; i < str.length(); ++i){
    if(key >= 0){
      while(key < 32 or key > 128){
	key -= str[i];
      }

      while(key >= 33 && key <= 127){
	encr_str.push_back(key);
	key -= str[i] / str.length();
      }

      key = key_store;
    }
  }
  
  return encr_str;
}
