README Documentation

Team Members:
Jacob Le 
Peter Estrada 

Edoras Accounts:
Jacob - cssc3738
Peter - cssc3726  (Note: Files are in my account)

CS530 for M/W 5:30PM Spring 2021

Project #2 

Filename: README

Compiling Instructions:
$ make
- This command inside the command line will compile all the appropriate files and make an ESTAB and executable object code file in accordance to the listing files

Design Decisions: 
1. When starting out the project, we decided that we wanted to create 2 functions, one that will handle creating the ESTAB and the other executable object file. Knowing this, we made both functions read the listing files and create their respective files.
2. We also decided that we wanted to use a few global variables to hold our vectors which will hold the global address of a certain control sections so that our 2 functions can reference them.
3. When working with the project, we realized that there needed to be hex addition for when creating the EXTDEF locations so we implemented functions to use to do that. We opted to use separate functions to do a hex addition. Since the hex were in string type, we had to use multiple functions to turn them into int, add them, then turn the answer back into string. 

Operating Instructions:
$ led <filename>.sl <filename2>.sl etc...
- This instruction essentially calls led and the following arguments after are the listing files that would want to be read into the program and create the executable object file and ESTAB
- If only less than or equal to 1 argument is passed into the command line, there will be a message stating that there needs to be at the minimum, 2 files

List of Deficiencies/Bugs:
1. A deficiency that we ran into is that if the address of a certain line is not equal to a number value, we won't be able to find the address of a particular EXTDEF.
2. This was the most obvious bug, but there might be some small bugs we did not catch even though we tested multiple files.

Lessons Learned:
1. From this project, we learned numerous things about I/O and reading files through C++.
a. We had to thoroughly understand how the command line understood input/output from within' C++ which was essential for this project as we are reading in files and going through them to attain data.
b. It was also essential that we were able to create the appropriate files that correspond to being the ESTAB and executable object file from how we read the files.
2. We ran into a problem of documentation where we were unable to figure out each other's code and what we were aiming to do with it. We realized that and decided to use GitHub and make calls to each other to work on it together so that we were on the same page on how we wanted to implement our program.
3. A big lesson to take away with this is that managing our time properly to get certain tasks done is essential. As we were closing in on the deadline, we realized that we should have allocated more time just in case for problems that we face and deal with them ahead of time. 
