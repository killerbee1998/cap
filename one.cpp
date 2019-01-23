#include "one.h"

bool one::init(std::string project_name){
    
  std::string default_p, project_p; //path to default and project
  
  std::string cap_config_p = util::get_cap_path() +"/config"; //path to cap config files
  std::string default_f_p = cap_config_p + "/default_path.txt";
  std::string editor_f_p = cap_config_p + "/default_editor.txt";
  std::string project_list_p = cap_config_p + "/project_list.txt";
  
  if(!util::is_file_present(default_f_p)){ //if not present create default pathfile
    std::ofstream default_f_out(default_f_p, std::ios::out);
    default_f_out << "/home/" << getenv("USER") << "/Documents" << std::endl;
    default_f_out.close();
  }

  if(!util::is_file_present(editor_f_p)){ //if not present create default editor file
    std::ofstream editor_f_out(editor_f_p, std::ios::out);
    editor_f_out << "vi" << std::endl;
    editor_f_out.close();
  }
 
  std::ifstream default_f_in(default_f_p, std::ios::in); //read default file
  default_f_in >> default_p;
  default_f_in.close();
  
  project_p = default_p + "/" +project_name; //set project file path
  
  bool project_absent = !util::is_project_present(project_name);
    
  if(project_absent){ // if project doesnt exist, write into list
    std::ofstream project_list_f_out(project_list_p, std::ios::out| std::ios::app);  
    project_list_f_out << "\n" << project_p << std::endl;
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
    pass = util::encrypt(pass);
    user_f_out << name << "\n" << pass << std::endl;
    mkdir(std::string(current_f_p + "/" + name).c_str(), 0700);
  }
  user_f_out.close();

  std::string kill; //set up kill code
  std::cout << "Provide the kill code" << std::endl;
  std::cin >> kill;
  kill = util::encrypt(kill);
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
      
      std::string name, pass;
      std::cout <<  "Please provide username ";
      std::cin >> name;
      std::cout << "Please provide password ";
      std::cin >> pass;
      
      std::ifstream user_f_in(user_f_p, std::ios::in);
      std::string line;
      bool user_present = false;
      while(std::getline(user_f_in, line)){
	if(line == name){ //if username is right
	  std::getline(user_f_in, line);
	  if(line == util::encrypt(pass)){ //if password is right
	    user_present = true;
	    
	  }else{ //if password is wrong
	    std::cout << "Invalid Password" <<std::endl;
	  }
	  
	}
      }
      user_f_in.close();
      
      if(user_present){	//if both password and username is right
	std::ofstream login_f_out(login_f_p, std::ios::out | std::ios::trunc);
	login_f_out << name << "*" << "logged";
	logged = true;
	util::write_local_log(project_name, name, "Logged in");
	login_f_out.close();
	
      }else{ //if username and password dont match
	std::cout << "Invalid user. Either username or password is wrong" << std::endl;
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

  if(util::is_project_present(project_name)){
    
    if(util::is_logged(project_name)){
      std::string login_f_p = util::get_project_path(project_name) + "/config/login.txt";
      
      util::write_local_log(project_name, util::get_logged_name(project_name), "Logged out");
      
      std::ofstream login_f_out(login_f_p, std::ios::out | std::ios::trunc);
      login_f_out.close();
      logged_out = true;
      std::cout << "Logged out" <<std::endl;

    }else{
      std::cout << "Already logged off" <<std::endl;
    }

  }else{
    std::cout << "Project not present" << std::endl;
    std::cout << "Initialoze project to  use this command" << std::endl;
  }

  return logged_out;

}

bool one::destroy(std::string project_name){

  bool destroyed = false;

  if(util::is_project_present(project_name)){

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
      kill = util::encrypt(kill);
      
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

  }else{
    std::cout << "Project not present" << std::endl;
    std::cout << "Initialize project to  use this command" << std::endl;
  }
  
  return destroyed;
}

//explore needs another file if it keeps growing, until then it stays open

bool one::explore(std::string project_name){

  util::update_dir(project_name);

  if(util::is_project_present(project_name)){
    bool quit = false;
    std::string path = util::get_project_path(project_name);

    if(!util::is_logged(project_name)){
      std::cout << "You most log in to perform this action" <<std::endl;
      quit = true;
    }else{
      path+="/current/"+util::get_logged_name(project_name);
    }

    while(!quit){
      std::string ls = "ls -l " + path;
      system(ls.c_str());

      std::string explorer_cmd;
      std::cout << "\nType open to open a File/Directory" << std::endl;
      std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Type back to go back to the previous Directory" << std::endl;
      std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Type editor to open the default editor"  << std::endl;
      std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Type shell to execute shell commands" << std::endl;
      std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Type del to delete a file" << std::endl;
      std::cout << "---------------------------------------------------------------------------------------------" << std::endl;
      std::cout << "Press q to quit" << std::endl;
      std::cin >> explorer_cmd;
      
      for(unsigned int i=0;i<explorer_cmd.length();++i){
	explorer_cmd[i] = std::tolower(explorer_cmd[i]); //ensures all commands are in lowercase
      }

      if(explorer_cmd == "q"){
	quit = true;

      }else if(explorer_cmd == "open"){

	std::string response;
	std::cout << "Enter name of File/Directory you wish to open" << std::endl;
	std::cin >> response;
	
	struct stat st = {0};
	if(stat(std::string(path + "/" + response).c_str(), &st) == 0){
	    
	  if(st.st_mode & S_IFDIR){ //if path points to a directory
	    path += "/" + response;
	    std::cout << "Now exploring " << path << std::endl;
	      
	  }else if(st.st_mode & S_IFREG){ //if path points to a file
	    std::string file_path = path + "/" + response;
	    
	    if(st.st_mode & S_IXUSR){ //if file is an executeable then execute in
	      system(std::string( "./" + file_path).c_str());
	      util::write_local_log(project_name, util::get_logged_name(project_name), "Executed " + response);

	    }else{  //if its not an executeable then open it in an editor
	      std::ifstream ed_in(util::get_cap_path() + "/config/default_editor.txt", std::ios::in);
	      std::string ed;
	      std::getline(ed_in, ed);
	      ed_in.close();
	      system(std::string(ed + " " + file_path).c_str());
	      util::write_local_log(project_name, util::get_logged_name(project_name), "Edited " + response);
	    }
	    
	  }else{
	    std::cout << "Object is neither a file nor a directory" << std::endl;
	    return true;
	  }

	}else{
	  std::cout << "File / Directory not present" << std::endl;
	  std::cout << "Would you like to create the file? [Y/N]" << std::endl;
	  char ans;
	  std::cin >> ans;
	  if(ans=='Y' || ans=='y'){
	    if(response.find('.')!=std::string::npos){
	      std::ofstream new_file(path+"/"+response, std::ios::out);
	      new_file.close();
	      std::cout << "A file named " + response + "has been opened" << std::endl;
	      util::write_local_log(project_name, util::get_logged_name(project_name),  "A File named " + response + "has been opened");
	    }else{
	      mkdir(std::string(path+"/"+response).c_str(),0700);
	      std::cout << "A Directory named " + response + "has been opened" << std::endl;
	      util::write_local_log(project_name, util::get_logged_name(project_name),  "A Directory named " + response + "has been opened");
	    }
	  }
	}
	
      }else if(explorer_cmd == "editor"){
	std::string editor_f_p = std::string("/home/") + getenv("USER") + "/Documents/cap/config/default_editor.txt";
	std::ifstream editor_f_in(editor_f_p, std::ios::in);
	std::string editor_cmd, cd;
	std::getline(editor_f_in, editor_cmd);
	editor_f_in.close();
	system(std::string(editor_cmd).c_str());
	util::write_local_log(project_name, util::get_logged_name(project_name),  "Opened default editor ");

      }else if(explorer_cmd == "shell"){
	std::cout << "Type the command in one line" << std::endl;
	std::string shell_cmd;
	std::getline(std::cin>>std::ws, shell_cmd);
	system(shell_cmd.c_str());

      }else if(explorer_cmd == "del"){
	std::string response;
	std::cout << "Enter name of File/Directory you wish to delete" << std::endl;
	std::cin >> response;
	struct stat st = {0};
	if(stat(std::string(path + "/" + response).c_str(), &st) ==0){
	  std::cout <<"This file will be deleted forever. Are you sure you want to delete? [Y/N]" << std::endl;
	  char ans;
	  std::cin >> ans;
	  if(ans == 'y' || ans == 'Y'){
	    std::string del_cmd = "rm ";
	    if(st.st_mode & S_IFDIR){ //if path points to a directory
	      del_cmd += "-rf ";
	      std::cout << "Directory at path " << path + "/" + response << "is deleted" << std::endl;
	    }else{
	      del_cmd += "-f ";
	      std::cout << "File at path " << path + "/" + response << "is deleted" << std::endl;
	    }
	    del_cmd += path + "/" + response;
	    system(del_cmd.c_str());
	    
	  }else{
	    std::cout << "File/Directory at path " << path + "/" + response << "is not deleted" << std::endl;
	  }
	  
	}else{
	  std::cout << "File/Directory does not exist, try again" << std::endl;
	}
      }else if(explorer_cmd == "back"){
	std::string temp = path;
	for(int i = temp.length()-1;i>-1;--i){
	  if(temp[i] == '/'){
	    temp.pop_back();
	    break;
	  }else{
	    temp.pop_back();
	  }
	  if(temp.length()>=util::get_project_path(project_name).length()){
	    path = temp;
	  }
	}
	  
      }else{
	std::cout << "Invalid command" << std::endl;
      }
    }
    
  }else{
    std::cout << "Project doesnt exist" << std::endl;
  }
  
  return true;
}

/*
bool one::cd(std::string project_name){

  util::update_dir(project_name);
  
  bool success = false;

  if(util::is_project_present(project_name)){
    
    if(util::is_logged(project_name)){
      std::string path = util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name);
      
      std::string cd_cmd = "cd " + path;
      
      system(std::string (cd_cmd + " && exec bash").c_str());
      success = true;
       
   }else{
      std::cout << "Not logged" << std::endl;
      std::cout << "Log in to use this command" << std::endl;
      
    }

  }else{
    std::cout << "Project not present" << std::endl;
    std::cout << "Initialize project to  use this command" << std::endl;
  }

  return success;
}
*/
