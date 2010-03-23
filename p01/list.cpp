/**
 * Namespace for list operations
 */

#include "P1.h"

namespace list
{
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

	/**
	 * Removes duplicate list entries
	 *
	 * @return
	 */
	int remove_duplicates()
	{
		/* Travel through list and compare each Item to each other */
		if (root == NULL)
		{
			cout << "ERROR: There are no entries in your list. Sorry, dude!" << endl;
		}
		else 
		{
			Anmeldung* master = root; // compare MASTER to SLAVE
			current = master->next; // SLAVE
			Anmeldung* previous = root;
			bool removed = false;
			
			while(master != NULL)
			{
				while(current != NULL && !removed)
				{
					/* Compare Matrikelnummern -- on positive result, free memory at master
					and relink remaining list-elements */
					if(master->Matrikelnummer == current->Matrikelnummer)
					{
						previous->next = master->next;
						if(master == root)
						{
							root = master->next;
						}
						
						delete master;
						
						master = previous->next;
					}
					
					current = current->next;
				}
				
				previous = master;
				
				if(!removed)
				{
					master = master->next;
				}
				
				if(master != NULL)
				{
					current = master->next;
				}
				
				removed = false;
			}
		}
		
		return 0;
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
	
	/**
	 * Returns the address of root
	 *
	 * @return	Anmeldung* root	Pointer
	 */
	Anmeldung* get_root()
	{
		return root;
	}
	
	/**
	 * Clears memory
	 *
	 * @return Anmeldung* element	Pointer
	 */
	bool destroy(Anmeldung* element) 
	{
		Anmeldung* temp;
		try
		{
			while(element != NULL)
			{
				temp = element;
				element = element->next;
				delete temp;
			}
		}
		catch(exception& e)
		{
			cout << "ERROR: Couldn't clear memory" << endl;
			
			return 0;
		}
		
		return 1;
	}
	
}