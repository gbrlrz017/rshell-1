RSHELL(hw0) + cp(lab5) + ls(hw1)
======================================================

Program Overview
------------------------------------------------------
1. RShell is a basic command shell, whcih can perform:

	(1) Print a command prompt which include loginname, hostname, and "$".

	(2) Read in a command or use connecter command such as "&&" or ";" to read in several commands.

	(3) Execute the command.

	(4) Use "exit" to exit rshell.

2. command ```cd``` is implemented and added, which can perform:

	(1) When there is not optional argument, copy the source file to the destination file with the most efficient cp method.

	(2) When there is optional argument, first print wallclock, user, and system run times, then copy the source file to the destination file.

3. command ```cd``` is implemented and added, which can perform:

	(1)

All sources can be downloaded from https://github.com/mxu008/rshell.git
------

Licensing information: See LICENSE
------

Author 
--------------------
Mengyi Xu

File List
--------------------
```
LICENSE

Makefile

README.md

./src

./tests
```
```
./src:
Timer.h

cp.cpp

main.cpp
```
```
./tests:

exec.script
```

How to run rshell 
-----------------------------------------------------

1. ```$ git clone https://github.com/mxu008/rshell.git``` 
2. ```$ cd rshell```
3. ```$ make```
4. ```$ bin/rshell```

How to run cp
-----------------------------------------------------

1. ```$ git clone https://github.com/mxu008/rshell.git```
2. ```$ cd rshell```
3. ```$ make```
4. ```$ bin/cp```

How to run ls
-----------------------------------------------------

1. ```$ git clone https://github.com/mxu008/rshell.git```
2. ```$ cd rshell```
3. ```$ make```
4. ```$ bin/ls```

Bugs
---------

* If there is space between multiple commands and connected by connectors, the shell will not work peoperly..

* "&&" and "||" do not work properly when there is invalid command.

* ";" can not connect a empty command.

 
