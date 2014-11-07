MFLAHS = -Wall -Werror -ansi -pedantic

all: 
	mkdir bin
	g++ $(MFLAGS) src/main.cpp -o bin/rshell
	g++ $(MFLAGS) src/cp.cpp -o bin/cp

rshell:
	mkdir bin
	g++ $(MFLAGS) src/main.cpp -o bin/rshell 

cp:
	mkdir bin
	g++ $(MFLAGS) src/cp.cpp -o bin/cp

clean:
	rm -rf bin
