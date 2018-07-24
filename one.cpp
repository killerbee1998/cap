#include "one.h"

bool one::init(std::string project_name){
    
  std::string default_p, project_p; //path to default and project
  
  std::string cap_config_p =  "/home/" + std::string(getenv("USER")) + "/Documents/cap/config/"; //path to cap config files
  std::string default_f_p = cap_config_p + "default.txt"; 
  std::string project_list_p = cap_config_p + "project_list.txt";
  
  if(!util::is_file_present(default_f_p)){ //if not present create default file
    std::ofstream default_f_out(default_f_p, std::ios::out);
    default_f_out << "/home/" << getenv("USER") << "/Documents" << std::endl;
    default_f_out.close();
  }
  
  std::ifstream default_f_in(default_f_p, std::ios::in); //read default file
  default_f_in >> default_p;
  default_f_in.close();
  
  project_p = default_p + "/" +project_name; //set project file path
  
  bool project_absent = !util::is_project_present(project_name);
  
  if(project_absent){ // if project doesnt exist, write into list
    std::ofstream project_list_f_out(project_list_p, std::ios::out| std::ios::app);
    project_list_f_out << project_p << std::endl;
    project_list_f_out.close();
    
  }else{  //else abort
    std::cout << "Project already present" << std::endl;
    return project_absent;
  }
  
  std::string project_config_p = project_p + "/config";  //path to project config
  std::string user_f_p = project_config_p + "/users.txt"; //user files,
  std::string kill_f_p = project_config_p + "/kill.txt";//kill files
  std::string date_f_p = project_config_p + "/date.txt";// date files
  std::string current_f_p = project_p + "/current"; //current dir
  
  mkdir(project_p.c_str(), 0700); //create project directory,
  mkdir(current_f_p.c_str(), 0700); //current directories,
  mkdir(project_config_p.c_str(), 0700); //config directory
  
  unsigned int user_num;
  std::string name, pass; //set up user directories
  std::ofstream user_f_out(user_f_p, std::ios::out);
  std::cout << "Enter number of users ";
  std::cin >> user_num;
  
  if(std::cin.fail()){
    std::cout << "Please enter a number not a character" <<std::endl;
    while(std::cin.fail()){
      std::cin >> user_num;
    }
    return false;
  }
  
  for(unsigned int i = 0; i < user_num; ++i){
    std::cout << "Enter " << i+1 << "th users name ";
    std::cin >> name;
    std::cout << "Enter " << i+1 << "th users password ";
    std::cin >> pass;
    user_f_out << name << "*" << pass << std::endl;
    mkdir(std::string(current_f_p + "/" + name).c_str(), 0700);
  }
  user_f_out.close();

  std::string kill; //set up kill code
  std::cout << "Provide the kill code" << std::endl;
  std::cin >> kill;
  std::ofstream kill_f(kill_f_p, std::ios::out);
  kill_f << kill;
  kill_f.close();

  std::ofstream date_f_out(date_f_p, std::ios::out);
  date_f_out << util::get_date();
  date_f_out.close();

  util::write_global_log(project_name, "Started project");
  
  return project_absent;
}

bool one::login(std::string project_name){

  bool logged = false;
  util::update_dir(project_name);
  
  if(!util::is_project_present(project_name)){
    std::cout << "Project not present" << std::endl;
    std::cout << util::get_project_path(project_name) << std::endl;
  
  }else{
  
    if(!util::is_logged(project_name)){

      std::string login_f_p = util::get_project_path(project_name) + "/config/login.txt";
      std::string user_f_p = util::get_project_path(project_name) + "/config/users.txt";
      
      std::string name, pass, user;
      std::cout <<  "Please provide username ";
      std::cin >> name;
      std::cout << "Please provide password ";
      std::cin >> pass;
      user = name + "*" + pass;
      
      std::ifstream user_f_in(user_f_p, std::ios::in);
      std::string line;
      bool user_present = false;
      while(std::getline(user_f_in, line)){
	if(line == user){
	  user_present = true;
	}
      }
      user_f_in.close();

      if(user_present){	
	std::ofstream login_f_out(login_f_p, std::ios::out | std::ios::trunc);
	login_f_out << name << "*" << "logged";
	logged = true;
	util::write_local_log(project_name, name, "Logged in");
	login_f_out.close();

      }else{
	std::cout << "User not  present" << std::endl;
      }

    }else{
      std::cout << "Already logged in" <<std::endl;
    }
  }

  return logged; 
}

bool one::logout(std::string project_name){

  bool logged_out = false;

  util::update_dir(project_name);

  if(util::is_logged(project_name)){
    std::string login_f_p = util::get_project_path(project_name) + "/config/login.txt";
    
    util::write_local_log(project_name, util::get_logged_name(project_name), "Logged out");
    
    std::ofstream login_f_out(login_f_p, std::ios::out | std::ios::trunc);
    login_f_out.close();
    logged_out = true;
    std::cout << "Logged out" <<std::endl;
  }  

  return logged_out;

}

bool one::destroy(std::string project_name){

  bool destroyed = false;

  if(!util::is_logged(project_name)){
    std::cout << "Not logged in" << std::endl;
    std::cout << "Log in to execute this command" << std::endl;

  }else{

    std::string login_p = util::get_project_path(project_name) + "/config/login.txt";
    std::string kill_p = util::get_project_path(project_name) + "/config/kill.txt";
    
    std::string name = util::get_logged_name(project_name);

    std::string kill;
    std::cout << "Enter kill code ";
    std::cin >> kill;

    std::ifstream kill_f_in(kill_p, std::ios::in);
    std::string line;
    kill_f_in >> line;
    kill_f_in.close();

    if(line == kill){
      bool sure = false;
      std::string confirm;
      std::cout << util::get_project_path(project_name) << " Will be destroyed";
      std::cout << ". Is this okay?" << std::endl;
      std::cout << "Press y to confirm" <<std::endl;
      std::cin >> confirm;
      if(confirm == "y" || confirm == "Y"){
	sure = true;
      }

      if(sure){
	system(std::string("rm -r " + util::get_project_path(project_name)).c_str());
	std::cout << "Project destroyed" << std::endl;
	util::remove_line("/home/" + std::string(getenv("USER")) + "/Documents/cap/config/project_list.txt", util::get_project_path(project_name));
	destroyed = true;

      }else{
	std::cout << "Destruction aborted" <<std::endl;
	util::write_local_log(project_name, name, "Tried to destroy project");
      }

    }
  }

  return destroyed;
}
      
