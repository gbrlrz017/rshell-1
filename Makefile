MFLAHS = -Wall -Werror -ansi -pedantic

all: rshell

rshell:
	mkdir bin
	g++ $(MFLAGS) src/main.cpp -o bin/rshell 

clean:
	rm -rf bin
