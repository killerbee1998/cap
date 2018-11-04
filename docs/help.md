__WELCOME TO THE HELP MENU FOR CAP, THE SIMPLE FILE MANAGER__

__INDEX:__

	__FORMAT__

	       N. command : cap command args[1...n]

	__ZERO ARGUMENT:__
	
	       1. help : cap help

	       2. c-def : cap c-def

        __ONE ARGUMENT:__

	      1. init : cap init project_name
	      
	      2. login : cap login project_name
	      
	      3. logout : cap logout project_name
	      
	      4. destroy : cap destroy project_name

	      5. explore : cap explore project name
	      
__COMMANDS:__

	__ZERO ARGUMENT:__

	      1. help : Opens the help file. The help file contains a list of
	      commands for cap.

	      Arguments : None.

	      Example : cap help

	      2. c-def: Change the default directory when creating a new project
	      .The current defaulr directory is ~/Documents/cap.

	      Arguments : None

	      Example : cap c-def

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

	      Example: cap init project_name

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

	     Example: cap login project_name

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

	     Example: cap logout project_name
					   
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

             Example: cap destroy project_name

	     5. explore : Explores the project.Sevral functions are
	     		  available while exploring.See the prompt
			  on how to use these functions.

			  Several of these functions include:

			  1)open : opens a file/directory. If its an
			  editable file, it opens the file in an editor.
			  Otherwise the file is executed.

			  2)back: goes back one directory. Fails if you try
			  to go outside the project.

			  2)editor : opens the default editor on the projects
			  location.

			  3)shell : executes a subshell script. *NOTE:
			  use && exec bash if you want your bash script
			  to effect the current process, otherwise the
			  script will execute in an different subshell*

			  4)del : delets a file. User must input the
			  file/directory name. Fails if file does not
			  exist.

			  5)q : short for quit. Quits exploring


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

             Example: cap explore project_name