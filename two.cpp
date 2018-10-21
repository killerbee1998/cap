#include "two.h"

bool two::add(std::string file_path, std::string project_name){

  bool success = false;

  util::update_dir(project_name);

  if(!util::is_project_present(project_name)){
    std::cout << "Project not present" <<std::endl;
    std::cout << "Initialize " << project_name << " to execute this command";

  }else if(!util::is_logged(project_name)){
    std::cout << "Log in to execute this command" <<std::endl;

  }else if(!util::is_file_present(file_path)){
    std::cout << file_path << " File Not present" << std::endl;

  }else{

     std::string file_name, tmp;
    for(int i = file_path.length() - 1;file_path[i] != '/'; --i){
      tmp.push_back(file_path[i]);
    }

    for(int i = tmp.length() - 1; i > -1; --i){
      file_name.push_back(tmp[i]);
    }
    
    std::string dest = util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name) + "/" + file_name;
    
    if(util::is_file_present(dest)){
      std::string response;
      std::cout << "File already exists. Type y to overwrite" <<std::endl;
      std::cin >> response;
      if(response == "y" || response == "Y"){
	std::cout << "File Overwritten\n";
	system(std::string("rm -rf " + dest).c_str());
      }else{
	std::cout << "File not overwritten\n";
	return false;
      }
    }    
    
    std::string cp = "cp " + file_path + " " + file_name;
    std::string cd = "cd " + util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name);
    
    if(system(std::string(cd + " && " + cp).c_str()) < 0){
      std::cout << "operation failed\n";
    }else{
      success = true;
      util::write_local_log(project_name, util::get_logged_name(project_name), "Added file " + file_name);
    }
    
  }

    return success;
}

bool two::add_dir(std::string dir_path, std::string project_name){

  bool success = false;

  util::update_dir(project_name);
  
  if(!util::is_project_present(project_name)){
    std::cout << "Project not present" <<std::endl;
    std::cout << "Initialize " << project_name << " to execute this command";
    
  }else if(!util::is_logged(project_name)){
    std::cout << "Log in to execute this command" <<std::endl;
    
  }else if(!util::is_file_present(dir_path)){
    std::cout << dir_path << " Directory Not present" << std::endl;
 
  }else{
    std::string dir_name, tmp;
    for(int i = dir_path.length() - 1;dir_path[i] != '/'; --i){
      tmp.push_back(dir_path[i]);
    }
    
    for(int i = tmp.length() - 1; i > -1; --i){
      dir_name.push_back(tmp[i]);
    }
    
    std::string dest = util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name) + "/" + dir_name;
    
    if(util::is_file_present(dest)){
      std::string response;
      std::cout << "Directory already exists. Type y to overwrite" <<std::endl;
      std::cin >> response;
      if(response == "y" || response == "Y"){
	std::cout << "File Overwritten\n";
	system(std::string("rm -rf " + dest).c_str());
      }else{
	std::cout << "File not overwritten\n";
	return false;
      } 
    }
    
    std::string cp = "cp -r " + dir_path + " " + dir_name;
    std::string cd = "cd " + util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name);
    
    if(system(std::string(cd + " && " + cp).c_str()) < 0){
      std::cout << "operation failed\n";
      
    }else{
      success = true;
      util::write_local_log(project_name, util::get_logged_name(project_name), "Added Directory " + dir_name);
      
      }
    
  }
  
  return success;
}

bool two::sub(std::string file_name, std::string project_name){

  bool success = false;

  util::update_dir(project_name);

  if(!util::is_project_present(project_name)){
    std::cout << "Project not present" <<std::endl;
    std::cout << "Initialize " << project_name << " to execute this command";

  }else if(!util::is_logged(project_name)){
    std::cout << "Log in to execute this command" <<std::endl;

  }else{
    std::string dest = util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name) + "/" + file_name;
  
    if(util::is_file_present(dest)){
      std::string response;
      std::cout << "Remove file? " << dest <<std::endl;
      std::cout << "Press y to remove" <<std::endl;
      std::cin >> response;
      if(response == "y" || response == "Y"){
	std::cout << "File removed\n";
	system(std::string("rm -f " + dest).c_str());
	success = true;
	util::write_local_log(project_name, util::get_logged_name(project_name), "Removed File " + file_name);

      }else{
	std::cout << "File not removed\n";
      }

    }else{
      std::cout << "File not present" << std::endl;
    }   
    
  }
    
  return success;
}

bool two:: sub_dir(std::string dir_name, std::string project_name){

  bool success = false;
  
  util::update_dir(project_name);

  if(!util::is_project_present(project_name)){
    std::cout << "Project not present" <<std::endl;
    std::cout << "Initialize " << project_name << " to execute this command";
    
  }else if(!util::is_logged(project_name)){
    std::cout << "Log in to execute this command" <<std::endl;
    
  }else{
  
    std::string dest = util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name) + "/" + dir_name;
    
    if(util::is_file_present(dest)){
      std::string response;
      std::cout << "Remove directory? " << dest << std::endl;
      std::cout << "Press y to remove" <<std::endl;
      std::cin >> response;
      if(response == "y" || response == "Y"){
	std::cout << "Directory removed\n";
	system(std::string("rm -rf " + dest).c_str());
	success = true;
	util::write_local_log(project_name, util::get_logged_name(project_name), "Removed Directory " + dir_name);
	
      }else{
	std::cout << "Directory not removed\n";
      }
      
    }else{
      std::cout << "Directory not present" << std::endl;
    }
    
  }
  
  return success;
}

bool two::add_new(std::string file_name, std::string project_name){

  std::string file_path = util::get_project_path(project_name) + "/current/" + util::get_logged_name(project_name) + "/" + file_name;
  bool overwrite = true;
  
  if(util::is_project_present(project_name)){
    
    std::ifstream f_in(file_path, std::ios::in);
    if(f_in.is_open()){
      
      std::string ov;
      std::cout << "File already exists. Overwrite? y/n" << std::endl;
      std::cin >> ov;

      if(ov == "n" || ov == "N"){
	overwrite = false;
      }
    }
    
    f_in.close();
    
    if(overwrite){
      std::ofstream f_out(file_path, std::ios::out | std::ios::trunc);
      f_out.close();
      
      std::string ed;
      std::cout << "Do you want to open the file? y/n" << std::endl;
      std::cin >> ed;
      
      if(ed == "y" || ed == "Y"){
	std::ifstream oped(util::get_cap_path() + "/config/default_editor.txt", std::ios::in);
	std::string ed_cmd;
	std::getline(oped, ed_cmd);
	oped.close();
	
	ed_cmd +=  " " + file_path;
	system(ed_cmd.c_str());
      }
    }
      
  }else{
    std::cout << "Project not present" << std::endl;
  }
    
  return overwrite;
}
