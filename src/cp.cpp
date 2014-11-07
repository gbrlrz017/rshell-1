#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Timer.h"

using namespace std;

bool file_exists(const char *fileName)
{
	if (access(fileName, F_OK) != -1)
	{
		return 1; // file exists
	}
	return 0; // file does not exist
}

// Copy method for input.get() and output.put()
void copy1(int argc, char** argv)
{
	ifstream input;
	ofstream output;
	string inFile = argv[1];
	string outFile = argv[2];

	input.open(inFile.c_str());
	if (input.fail())
	{
		cout << "Error opening " << inFile << endl;
		exit(1);
	}
	output.open(outFile.c_str());
	if (output.fail())
	{
		cout << "Error opening " << outFile << endl;
		exit(1);
	}
		
	char tmp;

	input.get(tmp);
	while (input.good())
	{
		output.put(tmp);
		input.get(tmp);
	}

	input.close();
	output.close();
}

// Copy method for read() and write() one character
void copy2(int argc, char** argv)
{
	int fdi = open(argv[1], O_RDONLY);
	int fdo = open(argv[2], O_WRONLY | O_CREAT);

	chmod(argv[2], S_IRWXU);

	if ((fdi == -1) || (fdo == -1))
	{
		perror("open");
		exit(1);
	}

	char buf[1];
	memset(buf, 0, sizeof(buf));
	int error; 
	
	while (error = read(fdi, buf, 1))
	{
		if (error == -1)
		{
			perror("read");
			exit(1);
		}
		if (write(fdo, buf, 1) == -1)
		{
			perror("write");
			exit(1);
		}
	}
	if(close(fdi) == -1)
	{
		perror("close");
		exit(1);
	}
	if(close(fdo) == -1)
	{
		perror("close");
		exit(1);
	}
}

// Copy method for read() and write() one buffer
void copy3(int argc, char** argv)
{
	int fdi = open(argv[1], O_RDONLY);
	int fdo = open(argv[2], O_WRONLY | O_CREAT);

	chmod(argv[2], S_IRWXU);

	if ((fdi == -1) || (fdo == -1))
	{
		perror("open");
		exit(1);
	}

	char buf[sizeof(BUFSIZ)];
	memset(buf, 0, sizeof(buf));
	int error; 
	
	while (error = read(fdi, buf, sizeof(buf)))
	{
		if (error == -1)
		{
			perror("read");
			exit(1);
		}
		if (write(fdo, buf, sizeof(buf)) == -1)
		{
			perror("write");
			exit(1);
		}
	}
	if(close(fdi) == -1)
	{
		perror("close");
		exit(1);
	}
	if(close(fdo) == -1)
	{
		perror("close");
		exit(1);
	}
}

int main(int argc, char** argv)
{
	// Check the number of argc
	if (argc < 3 || argc > 4)
	{
		cout << "cp: missing file operand\nTry `cp --help' for more information." << endl; 
	}
	
	// Check whether destination file is exists
	if (file_exists(argv[2]))
	{
		cout << "Error: " << argv[2] << " already exists." << endl;
		return 1;
	}
	
	// With optional argument then print out wallclock, user, and system run times for three methods
	if (argc == 4)
	{
		Timer t;
		double time;
		
		// Print times for input.get() and output.put()
		t.start();
		copy1(argc, argv);
		cout << "Times for input.get() and output.put(): " << endl;
		t.elapsedWallclockTime(time);
		cout << "Wallclock: " << time << endl;
		t.elapsedUserTime(time);
		cout << "User: " << time << endl;
		t.elapsedSystemTime(time);
		cout << "System: " << time << endl << endl;
		
		// Print times for read() and write() one character 
		t.start();
		copy2(argc, argv);
		cout << "Times for read() and write() one character: " << endl;
		t.elapsedWallclockTime(time);
		cout << "Wallclock: " << time << endl;
		t.elapsedUserTime(time);
		cout << "User: " << time << endl;
		t.elapsedSystemTime(time);
		cout << "System: " << time << endl << endl;
		
		// Print times for read() and write() one buffer
		t.start();
		copy3(argc, argv);
		cout << "Times for read() and write() one buffer: " << endl;
		t.elapsedWallclockTime(time);
		cout << "Wallclock: " << time << endl;
		t.elapsedUserTime(time);
		cout << "User: " << time << endl;
		t.elapsedSystemTime(time);
		cout << "System: " << time << endl << endl;

		return 0;	
	}
	
	// Without optional argument, then run the most efficient copy method
	if (argc == 3)
	{
		copy1(argc, argv);	
	}
	
	return 0;
}

