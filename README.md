# PhoneBookManagementSystem

mysql 			      ------- 	support library and include folder.
phonebookdir.sql 	------- 	database
PhoneBook 		    ------- 	source code


1) copy mysql folder to c drive
2) open code blocks 
	settings -> compiler -> linker settings -> add 
	browser 'libmysql.lib' in the mysql folder in lib folder
	path eg :- C:\MySql\content\lib\libmysql.lib

	Now in
	settings -> compiler -> search directories -> compiler -> add
	browse 'include' folder in mysql folder
	path eg :- C:\MySql\content\include
	
3) Than click on 'OK'

4) create new project console apllication in code blocks
5) copy paste the code from 'FinalPhoneBook.cpp' to 'main.cpp';

6)	watch this video to create your database after '8:30 min'
	
	https://www.youtube.com/watch?v=xdvVKywGlc0
	
	
	and the database structure will be like
	
	Name 		  --- varchar(30)
	Phone_No 	--- varchar(10);

	for a sample "database look.png" file is present in the folder.
