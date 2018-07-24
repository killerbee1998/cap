__WELCOME TO THE HELP MENU FOR CAP, THE SIMPLE FILE MANAGER__

__INDEX:__

	__ZERO ARGUMENT:__
	
	       1. help : NONE.

        __ONE ARGUMENT:__

	      1. init : project_name.
	      
	      2. login : project_name.
	      
	      3. logout : project_name.
	      
	      4. destroy : project_name.

        __TWO ARGUMENT:__

	      1. add : file_path, project_name.
	      
	      2. add-dir : dir_path, project_name.

	      3. sub : file_name, project_name.

	      4. sub-dir : : file_name, project_name.
	      
__COMMANDS:__

	__ZERO ARGUMENT:__

	      1. help: Opens the help file. The help file contains a list of
	      commands for cap.

	      Arguments: None.

	__ONE ARGUMENT:__

	      1. init : Creates a new project. Project must have a unique
	      name.

	      Fails if : I. Another project with the same name already
	      	       	 exists.
	      
	      	       	 II. The value of number of users is not an
			 unsigned integer.

              Arguments : I. project_name = Name of the project. Name
	      		     		    must be unique. Same name
					    cannot be used for different
					    projects. No project of the
					    same name may exist before
					    executing this command.

             2. login : Logs in as an user of the project.

	     Fails if : I. Username is incorrect.

	     	      	II. Password is incorrect.

			III. Project doesnt exist yet. See [one][1] init
			for details.

			IV. If user is already logged in.

             Arguments : I. project_name = Name of the project. Name
	      		     		   must be unique. Same name
					   cannot be used for different
					   projects.An actual project
					   must exist before executing
					   this command. See [one][1]
					   init for further details.

             3. logout : Logs out an an user ofthe project.

	     Fails if : I. Username is incorrect.

	     	      	II. Password is incorrect.

			III. Project doesnt exist yet. See [one][1] init
			for further details.

			IV. User has already logged out.

             Arguments : I. project_name = Name of the project. Name
	      		     		   must be unique. Same name
					   cannot be used for different
					   projects. An actual project
					   must exist before executing
					   this command. See [one][1]
					   init for further details.
					   
             4. destroy : Destroys the project in its entireity. Be
	                  extremely cautious while using this command.
			  Always check the given directory before deleting,
			  as failure to do so might lead to unrecoverable
			  loss of valuable data.

	     Fails if : I. Project doesnt exist yet. See [one][1] init
			for details.

			II. User is not already logged in. See [one][2]
			login for further details.

             Arguments : I. project_name = Name of the project. Name
	      		     		   must be unique. Same name
					   cannot be used for different
					   projects.An actual project
					   must exist before executing
					   this command. See [one][1]
					   init for further details.

        __TWO ARGUMENT:__

	      1. add : Inserts a file to the project.

	      Fails if : I. Project doesnt exist yet. See [one][1] init
			for details.

			II. User is not already logged in. See [one][2]
			login for further details.

			III. File is not present.

			IV. File path is invalid.

	     Arguments : I. file_path = Path of the file that must be
	     	       	    	      	added. An actual file must exist
					in the specified path, else this
					command will fail.

			 II. project_name = Name of the project. Name
	      		     		   must be unique. Same name
					   cannot be used for different
					   projects.An actual project
					   must exist before executing
					   this command. See [one][1]
					   init for further details.

         2. add-dir : Inserts a directory to the project. This command
      	    	      also works on files as well. May be use as a      
		      replacement to [two][1] add.

	     Fails if : I. Project doesnt exist yet. See [one][1] init
			 for details.
			 
			II. User is not already logged in. See [one][2]
			login for further details.

			III. Directory is not present.

			IV. Directory path is invalid.

	     Arguments : I. dir_path = Path of the directory that must be
	     	       	    	      	added. An actual file must exist
					in the specified path, else this
					command will fail.

			 II. project_name = Name of the project. Name
	      		     		   must be unique. Same name
					   cannot be used for different
					   projects.An actual project
					   must exist before executing
					   this command. See [one][1]
					   init for further details.
					   
	     3. sub : Deletes a specified file from the project. The file
	     will only be deleted in the current folder. Copies will
	     remain in their respective past directories.

	     Fails if : I. Project doesnt exist yet. See [one][1] init
			for details.

			II. User is not already logged in. See [one][2]
			login for further details.

			III. File is not present in the project.

			IV. File name is invalid.

	     Arguments : I. file_name = Name of the file that must be
	     	       	    	      	deleted. An actual file must exist
					in the specified path, else this
					command will fail.

			 II. project_name = Name of the project. Name
	      		     		   must be unique. Same name
					   cannot be used for different
					   projects.An actual project
					   must exist before executing
					   this command. See [one][1]
					   init for further details.
					   
	     3. sub-dir : Deletes a specified directory from the project.
	     The directory will only be deleted in the current folder.
	     Copies will remain in their respective past directories.

	     Fails if : I. Project doesnt exist yet. See [one][1] init
			for details.

			II. User is not already logged in. See [one][2]
			login for further details.

			III. Directory is not present in the project.

			IV. Directory name is invalid.

	     Arguments : I. dir_name = Name of the directory that must be
	     	       	    	      	deleted. An actual directory must
					exist in the specified path, else
					this command will fail.

			 II. project_name = Name of the project. Name
	      		     		   must be unique. Same name
					   cannot be used for different
					   projects.An actual project
					   must exist before executing
					   this command. See [one][1]
					   init for further details.
