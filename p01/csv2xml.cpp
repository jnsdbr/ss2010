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
 * Checks if source and destination fila are available
 *
 * @param string&	filname		Filename
 *
 * @return true if successfull, false if not
 */
bool check_file(string& filename)
{
	ifstream file;

	file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);

	// Check if source file is available
	try
	{
		file.open(filename.c_str());
		file.close();
	}
	catch(exception& e)
	{
		cout << "ERROR: file not found." << endl;

		return 0;
	}

	return 1;
}


namespace list
{
	static Anmeldung* root = NULL;
	static Anmeldung* current = NULL;
	
	/**
	 * Allocates memory for a new list item
	 *
	 * @return	Anmeldung*		Pointer of the new element
	 */
	Anmeldung* create()
	{
		Anmeldung* new_element = NULL;		
		new_element = new Anmeldung;

		new_element->next = NULL;

		return new_element;
	}
	
	/**
	 * Inserts an element into a list
	 *
	 * @param string	item[]		Array of Strings
	 *
     * @return true if successfull, false if not	
	 */
	bool insert(string item[])
	{		
		if(root == NULL)
		{
			try
			{
				root = create();
				current = root;				
			}
			catch(exception& e)
			{
				cout << "ERROR: Error while allocating Memory" << endl;
				return 0;
			}
		}
		else
		{
			try
			{	
				Anmeldung* new_element = NULL;
				new_element = create();
			
				current->next = new_element;
				current = new_element;
			}
			catch(exception& e)
			{
				cout << "ERROR: Error while allocating Memory" << endl;
				return 0;				
			}
		}		


		current->Nachname = item[0];
		current->Vorname = item[1];
		current->Email = item[2];
		current->Matrikelnummer = item[3];
		current->Studienrichtung = item[4];
		current->Semester = item[5];
		current->G1name = item[6];
		current->G1vorname = item[7];
		current->Anmerkung = item[8];
		
		return 1;
	}
	
	int remove_duplicates()
	{
		
	}
	
	/**
	 * Displays all elements of a list
	 */
	void show()
	{
		if(root != NULL)
		{
			current = root;
		
			while(current != NULL)
			{
				cout << "Vorname: " << current->Vorname << endl;	
				cout << "Nachname: " << current->Nachname << endl;
				cout << "E-Mail: " << current->Email << endl;
				cout << "MatrikelNr.: " << current->Matrikelnummer << endl;
				cout << "Studienrichtung: " << current->Studienrichtung << endl;		
				cout << "Semester: " << current->Semester << endl;
				cout << "G1 Name: " << current->G1name << endl;		
				cout << "G1 Vorname: " << current->G1vorname << endl;
				cout << "Anmerkung: " << current->Anmerkung << endl;
				cout << "---" << endl;
			
				current = current->next;	
			}
		}
		
	}
}

/**
 * Writes the list to a xml file 
 *
 * @param Anmelding*	list		Pointer of the list
 * @param string		destination	Name of the destination file
 *
 * @return true if successfull, false if not	 
 */
bool write_xml(Anmeldung* list, string destination)
{
	string xml_root_tag_begin = "<OOP_Praktikum>\n";
	string xml_root_tag_end =  "</OOP_Praktikum>\n";
	string xml_entity_tag_begin = "  <Anmeldung>\n";
	string xml_entity_tag_end = "  </Anmeldung>\n";
	
	string xml_output = xml_root_tag_begin;	
	
	ofstream file;
	
	if(list::root != NULL)
	{
		list::current = list::root;
		
		while(list::current != NULL)
		{
			xml_output += xml_entity_tag_begin;
		
			xml_output += "    <Nachname>" + list::current->Nachname + "</Nachname>\n";
			xml_output += "    <Vorname>" + list::current->Vorname + "</Vorname>\n";
			xml_output += "    <Email>" + list::current->Email + "</Email>\n";
			xml_output += "    <Matrikelnummer>" + list::current->Matrikelnummer + "</Matrikelnummer>\n";
			xml_output += "    <Studienrichtung>" + list::current->Studienrichtung + "</Studienrichtung>\n";
			xml_output += "    <Semester>" + list::current->Semester + "</Semester>\n";
			xml_output += "    <G1Name>" + list::current->G1name + "</G1Name>\n";
			xml_output += "    <G1Vorname>" + list::current->G1vorname + "</G1Vorname>\n";
			xml_output += "    <Anmerkung>" + list::current->Anmerkung + "</Anmerkung>\n";
			
			list::current = list::current->next;

			xml_output += xml_entity_tag_end;
		}
	}
	
	xml_output += xml_root_tag_end;
	
	try
	{
		file.open(destination.c_str());
		file << xml_output;
		file.close();
	}
	catch(exception& e)
	{
		cout << "Error: File could not be overwritten" << endl;
		return 0;
	}
	
	return 1;
}



/**
 * Reads the source file and saves it into a list
 *
 * @param string&	source			Source filename
 */
int read_file(string& source)
{
	string line;
	ifstream file;
	int found;
	int str_start = 0;
	int str_length = 0;
	string item[9];

	//file.exceptions(ifstream::eofbit | ifstream::failbit | ifstream::badbit);

	try
	{
		file.open(source.c_str());

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
						str_length = found - str_start;
						
						//cout << "SUBSTR: " << i << " - " << line.substr(str_start, str_length) << endl;
						item[i] = line.substr(str_start, str_length);
	
						str_start = found + 1;
					}
					if(i == 7)
					{
						//cout << "SUBSTR: " << i << " - " << line.substr(str_start, line.length() - str_start) << endl << "---" << endl;
						item[i+1] = line.substr(str_start, line.length() - str_start);
					}
				}
				str_start = 0;

				list::insert(item);
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

/**
 * main
 */
int main(int argc, char *argv[])
{
	if(check_arguments(argc, argv[1], argv[2]))
	{
		string source = argv[1];
		string destination = argv[2];
		
		if(check_file(source) && check_file(destination))
		{
			if(read_file(source))
			{
				write_xml(list::root, destination);
				cout << "Fine." << endl;
			}
		}				
	}

	return 0;
}
