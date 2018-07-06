#include "one_list.h"

util util;

bool one_list::init(std::string project_name){

  std::string LOCAL_USER_NAME = std::string(getenv("USER"));
  const std::string path ="/home/"+ LOCAL_USER_NAME + "/Documents/" + project_name;
  std::string current_dir = path + "/current";
  
  if(util.project_present(project_name)){
    return false;
  }
  
  std::ofstream project_file_out("projects.txt", std::ios::out);
  project_file_out << path << std::endl;
  project_file_out.close();
  
  mkdir(path.c_str(), 0700);  //make project directory with subdirctories
  mkdir(current_dir.c_str(), 0700);
  
  std::ofstream  member_file(path + "/members.txt", std::ios::out);//member file

  std::string date_file_path = path + "/dates.txt"; //path to log files
  
  util.write_current_time(date_file_path);
  util.write_global_log(project_name, "Successfullly started project");
  
  int member_num;
  std::cout << "Enter number of members in the project: ";
  std::cin >> member_num;
  for(int i=0;i<member_num;++i){
    
    std::string name, pass;
    std::string member_dir;
    std::cout << "Enter " << i+1 <<"th member's name ";
    std::cin >> name;
    std::cout << "Enter " << i+1 <<"th member's password ";
    std::cin >> pass;
    
    member_dir = current_dir + "/" + name;
    mkdir(member_dir.c_str(), 0700);
    
    std::string member_log_file_path = member_dir + "/log.txt";
    
    util.write_log(member_log_file_path, "Successfully started project");
    member_file << name << "*" << pass << std::endl;
  }
  
  member_file.close();
  
  return true;
}

bool one_list::login(std::string project_name){

  std::string line;

  if(!util.project_present(project_name)){
    std::cout << "Project not initialized" << std::endl;
    return false;
  }
  
  std::string name,pass, member;
  
  std::cout <<"Enter Username ";
  std::cin >> name;
  std::cout << "Enter Password ";
  std::cin >> pass;
  member = name + "*" + pass;

  std::ifstream login_file_in("login.txt" ,std::ios::in);
  while(std::getline(login_file_in, line)){
    if(line == "logged*" + project_name + "#" + name){
      std::cout << "Already logged into project " << project_name;
      std::cout << " As " << name << std::endl;
      return false;
    }
  }
  login_file_in.close();
  
  std::string project_path = "/home/" + std::string(getenv("USER")) + "/Documents/" + project_name;

  std::ifstream member_file(project_path + "/members.txt", std::ios::in);
  bool member_present; 
  while(std::getline(member_file, line)){
    
    if(line != member){
      member_present = false;
      
    }else{
      
      member_present = true;
      
      if(!util.line_present("login.txt", "logoff*"+project_name+"#"+name)){

	std::ofstream login_file_out("login.txt", std::ios::out | std::ios::app);
	login_file_out << "logged" << "*";
	login_file_out << project_name << "#";
	login_file_out << name << std::endl;
	login_file_out.close();
	
      }else{
	
	util.replace_line("login.txt", "logoff*"+project_name+"#"+name, "logged*"+project_name+"#"+name);
	
      }
      
      util.write_local_log(project_name, name, "Logged in");
      break;
    }
  }
  member_file.close();

  if(!member_present){
    std::cout << "Member not present" <<std::endl;
  }

  return  member_present;
}

bool one_list::logout(std::string project_name){

  bool logged_off;
  std::string project_path = "/home/" + std::string(getenv("USER")) + "/Documents" + project_name;
  
  if(!util.project_present(project_name)){
    std::cout << "Invalid Project Name" <<std::endl;
    return false;
  }
    
  std::string name;
  std::cout << "Enter Username ";
  std::cin >> name;

  if(util.line_present("login.txt", "logoff*"+project_name+"#"+name)){
    
    std::cout << "Already logged off" << std::endl;
    logged_off = false;
    
  }else if(util.line_present("login.txt", "logged*"+project_name+"#"+name)) {
    
    util.replace_line("login.txt", "logged*"+project_name+"#"+name, "logoff*"+project_name+"#"+name);
    util.write_local_log(project_name, name, "logged off");
    logged_off = true;

  }else{
    std::cout << "USER NOT PRESENT" << std::endl;
    logged_off = false;

  }
  
  return logged_off;
}
