#include "P1.h"

/**
 * Checks commandline arguments for errors
 *
 * @param int	count			Argument count (argc)
 * @param char	*source			Source filename
 * @param char	*destination	Destination filename
 */
int check_arguments(int count, char *source, char *destination)
{
	// No arguments
	if(count == 1)
	{
		cout << "CSV to XML Parser " << endl << "Usage: <source> <destination>" << endl;

		return 0;
	}

	// Not enough arguments
	if(count == 2)
	{
		cout << "ERROR: Not enough arguments." << endl;

		return 0;
	}

	// Too many arguments
	if(count > 3)
	{
		cout << "ERROR: Too many arguments." << endl;

		return 0;
	}

	// Source equals destination
	if(!strcmp(source, destination))
	{
		cout << "ERROR: Source and destination cant be the same file." << endl;

		return 0;
	}

	return 1;
}

/**
 * Checks if source and destination fila are available
 *
 * @param char	*source			Source filename
 * @param char	*destination	Destination filename
 */
int check_file(char *filename)
{
	ifstream file;

	file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);

	// Check if source file is available
	try
	{
		file.open(filename);
		file.close();
	}
	catch(exception& e)
	{
		cout << "ERROR: file not found." << endl;

		return 0;
	}

	return 1;
}

/**
 * Reads the source file and saves it into a list
 *
 * @param char	*source			Source filename
 */
int read_file(char * source)
{
	string line;
	ifstream file;
	int found;
	int str_start = 0;
	int str_length = 0;

	//file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);

	try
	{
		file.open(source);

		while(!file.eof())
		{
			getline(file, line, '\n');

			// Only if line is not empty
			if(line.length() != 0)
			{
				found = 0;

				for(int i = 0; i <= 7; i++)
				{
					found = line.find(";", found+1);

					if(found < string::npos)
					{
						str_length = int(found) - str_start;

						cout << "SUBSTR: " << line.substr(str_start, str_length) << endl;

						str_start = int(found) + 1;
					}
					if(i == 7)
					{
						cout << "SUBSTR: " << line.substr(str_start, line.length() - str_start) << endl;
						cout << "---" << endl;
					}
				}
				str_start = 0;
			}
		}

		file.close();
	}
	catch(exception& e)
	{
		cout << "ERROR: Error while reading source file." << endl;

		return 0;
	}

	return 1;
}

namespace list
{
	int insert(string anmerkung,
			   string email,
			   string g1name,
			   string g1vorname,
			   string matrikelnummer,
			   string nachname,
			   Anmeldung* next,
			   string semester,
			   string studienrichtiung,
			   string vorname)
	{
		// Hello! :)
	}
}


/**
 * main
 */
int main(int argc, char * const argv[])
{
	if(check_arguments(argc, argv[1], argv[2]))
	{
		if(check_file(argv[1]) && check_file(argv[2]))
		{
			if(read_file(argv[1]))
			{
				cout << "Fine." << endl;
			}
		}
	}

	return 0;
}
