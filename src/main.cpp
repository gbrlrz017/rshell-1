#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <string.h>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAX = 1000;

vector<char*> vstrToVchar(vector<string> vs)
{
	vector<char*> vc;	
			
	for (unsigned i = 0; i < vs.size(); ++i)
	{
		char* tmpChar = new char[vs[i].size() + 1];

		memcpy(tmpChar, vs[i].c_str(), vs[i].size() + 1);
		
		vc.push_back(tmpChar);
	}

	return vc;
}

void execCmd(vector<char*> vc)
{
	char* argv[sizeof(vc) + 1];
	unsigned i = 0;

	for (i = 0; i < vc.size(); ++i)
	{
		argv[i] = new char[vc.size() + 1];
		strcpy(argv[i], vc[i]);
	}
					
	argv[i] = 0;

	execvp(argv[0], argv);

}

void run(vector<char*> vc, char* hostname)
{
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		execCmd(vc);
		exit(1);
	}
	else
	{
		wait(NULL);
		cout << getlogin() << "@" << hostname << "$ ";
	}
}

int main()
{
	int len;
	char* str = new char[MAX];
	char hostname[100];
	
	// Get hostname
	gethostname(hostname, sizeof hostname);

	// Print username, hostname, and $
 	cout << getlogin() << "@" << hostname << "$ ";	

	// Create a infinite loop untill the input is "exit"
	while (1)
	{
		// Get the input string
		while (fgets(str, MAX, stdin) != 0)
		{
			len = strlen(str);
			if (str[len - 1] == '\n')
			{
				str[len - 1] = '\0';
				break;
			}
		}

		// If the input is "exit", then exit; 
		if (strcmp(str, "exit") == 0) exit(0);

		// Separate the string into commands and save them into a vector
		vector<string> vs;
		string tmp;

		if (str[0] == '\0')
		{
			cout << getlogin() << "@" << hostname << "$ ";
			continue;
		}

		while (str[0] == ' ')
		{
			for (unsigned i = 0; i < strlen(str); i++)
			{
				str[i] = str[i + 1];
			}
		}

		for (unsigned i = 0; str[i] != 0; ++i)
		{
			if (str[i] != ' ' && str[i] != ';' && str[i] != '&' && str[i] != '|')
			{
				tmp.push_back(str[i]);	
			}
			else if (str[i] == ';')
			{
				vs.push_back(tmp);
				tmp = "";

				int pid = fork();
				if (pid == -1)
				{
					perror("fork");
					exit(1);
				}
				else if (pid == 0)
				{
					vector<char*> tmpVC = vstrToVchar(vs);
				
					execCmd(tmpVC);
					exit(1);
				}
				else
				{
					wait(NULL);
					vs.pop_back();
					//continue;
				}	
			}
			else if (str[i] == '|')
			{
				if (str[i + 1] == '|')
				{
					vs.push_back(tmp);
					tmp = "";
					vector<char*> tmpVC = vstrToVchar(vs);
				
					char* tmpArgv [sizeof(tmpVC) + 1];
					unsigned j = 0;

					for (j = 0; j < tmpVC.size(); ++j)
					{
						tmpArgv[j] = new char[tmpVC.size() + 1];
						strcpy(tmpArgv[j], tmpVC[j]);
					}

					tmpArgv[j] = 0;

					int pid = fork();
					if (pid == -1)
					{
						perror("fork");
						exit(1);
					}
					else if (pid == 0)
					{
						if (-1 == execvp(tmpArgv[0], tmpArgv))
						{
							continue;	
						}
						exit(1);
					}
					else
					{
						wait(NULL);
						vs.pop_back();
					}
				}
				else
				{
					continue;
				}
			}
			else if (str[i] == '&')
			{
				if (str[i + 1] == '&')
				{
					vs.push_back(tmp);
					tmp = "";
					vector<char*> tmpVC = vstrToVchar(vs);

					char* tmpArgv [sizeof(tmpVC) + 1];
					unsigned j = 0;

					for (j = 0; j < tmpVC.size(); ++j)
					{
						tmpArgv[j] = new char[tmpVC.size() + 1];
						strcpy(tmpArgv[j], tmpVC[j]);
					}
			
					tmpArgv[j] = 0;					

					int pid1 = fork();
					if (pid1 == -1)
					{
						perror("fork");
						exit(1);
					}
					else if (pid1 == 0)
					{
						if (-1 == execvp(tmpArgv[0], tmpArgv))
						{
							break;
						}
						exit(1);
					}
					else
					{
						wait(NULL);
						vs.pop_back();
						int pid = fork();
						if (pid == -1)
						{
							perror("fork");
							exit(1);
						}
						else if (pid == 0)
						{
						//	execvp(tmpArgv[0], tmpArgv);
							exit(1);//
						}
						else
						{
							wait(NULL);
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}
			else
			{
				if (tmp != "")
				{
					vs.push_back(tmp);
					tmp = "";
				}
				else
				{
					continue;
				}
			}
		}
		vs.push_back(tmp);
		
		len = vs.size();

		//	for (int i = 0; i < len; ++i)
		//	{
		//		cout << vs[i] << endl;
		//	}
		
		// Change vector of string to vector of char*
		vector<char*> vc;
		vc = vstrToVchar(vs);

		// Create several processes and execute the commands
		run(vc, hostname);
	}
	
	return 0;
}
