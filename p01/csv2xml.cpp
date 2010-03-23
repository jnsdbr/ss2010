/**
 * CSV to XML converter
 * Converts csv formatted data into a xml file
 *
 * @author Boris Spinner & Jens de Boer 
 */

#include "P1.h"

/**
 * Checks commandline arguments for errors
 *
 * @param int	count			Argument count (argc)
 * @param char	*source			Source filename
 * @param char	*destination	Destination filename
 *
 * @return Returns true if there are no errors / else false
 */
bool check_arguments(int count, char *source, char *destination)
{
	// No arguments
	if(count == 1)
	{
		cout << "CSV to XML Parser - Authors: Jens de Boer & Boris Spinner" << endl << "Usage: <source> <destination>" << endl;

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
		cout << "ERROR: Source and destination are the same file." << endl;

		return 0;
	}

	return 1;
}

/**
 * main
 */
int main(int argc, char *argv[])
{
	if(check_arguments(argc, argv[1], argv[2]))
	{
		string source = argv[1];
		string destination = argv[2];
		
		if(file::check_file(source) && file::check_file(destination))
		{
			if(file::read_file(source))
			{
				try
				{
					list::remove_duplicates();
					file::write_xml(list::get_root(), destination);
					list::destroy(list::get_root());
					cout << "Fine." << endl;
				}
				catch(exception& e)
				{
					
				}
			}
		}				
	}

	return 0;
}
