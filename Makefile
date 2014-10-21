MFLAHS = -Wall -Werror -ansi -pedantic

all: rshell

rshell:
	mkdir bin
	g++ $(MFLAGS) src/hw0.cpp -o bin/rshell 

clean:
	rm -rf bin
