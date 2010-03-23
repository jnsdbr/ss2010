/**
 * Namespace for file operations
 */

#include "P1.h"

namespace file
{
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
			cout << "ERROR: " << filename << " not found" << endl;

			return 0;
		}

		return 1;
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

		if(list != NULL)
		{
			list::current = list::get_root();

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
}