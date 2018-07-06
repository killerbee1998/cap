___HELP FILE FOR CAP___

__This file contains a list of all the commands__
__along with their descriptions for CAP, the simple__
__project manager. See the manual for futher inquiries__

__Zero Argument Commands__

       1. help : Displays the help file, listing all
       commands.

	  Arguments : NONE.

__One Argument Commands__

      1. init : Initializes cap. See Initialize.md
      for details.

      	  Arguments : project_name :: Name of the project
	  you want to initialize. Project names must all
	  be unique. trying to initialize a second project
	  with the same name will result in a failure.

      2. login: Logs in as a member. Member must
      provide their username and password to login.
      Wrong username and passwords will result in a
      failed login. If member is already logged in,
      then the login will fail.

      	   Arguments : project_name  :: name of the project
	   you want to log in as a member. Fails if the project
	   does not exist and/or not yet initialized.


      3. logout : logs out of the project. Member must provide
      their username. If someone with the osernme is not logged
      in then it will result in a failed logout. Already logging
      out will also result in a failed logout.

      	  Arguments : project_name  :: name of the project
	   you want to log in as a member. Fails if the project
	   does not exist and/or not yet initialized.
