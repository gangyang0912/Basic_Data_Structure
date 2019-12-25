/****************************************************************************

                                                Gang Yang
                                                CSE 12, fall16
                                                11-04
                                                
                              Assignment 6

File Name:      Driver.c
Description:    This program let us build a hash table to hold the students'
                information. In the assignment, we are to implement a Symbol 
                Table to allow variable assignment to the calculator. 
                we are also to write the member functions for the UCSDStudent 
                class as part of the Driver.java file and the Driver.c file 
                used to test our symbol table.

****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <getopt.h>
#include "Base.h"
#include "SymTab.h"
#include <cstdlib>
using namespace std;

#ifdef NULL
#undef NULL
#define NULL 0
#endif
/* Class Header: UCSDStudent 
 * Description:  this class holds basic information of each student 
 * 				 and functions we will use later
 * Funtions:     UCSDStudent (char * nm, long sn)
 *				 ~UCSDStudent (void)
 *				 operator const char *(void) const
 *				 operator long (void) const 
 * 				 long operator == (const Base & base) const
 *				 long operator <(const Base & base) const
 *       		 ostream & Write (ostream & stream) const
 */
class UCSDStudent : public Base {
	char * name;
	long studentnum;
public:
	UCSDStudent (char * nm, long sn) :
		name (strdup (nm)), studentnum (sn) {}
	~UCSDStudent (void) {
		free (name);
	}

	/* get name funciton */
	/* return the name */
	operator const char * (void) const {  
        return name;  
	 } 

	 /* hash function */
	 operator long (void) const;

	 /* equal function */
	 /* return true or false */
	 long operator == (const Base & base) const {  
		return ! strcmp (name, base);  
	 }  

	 /* less than function */
	 /* return true or false */
	 long operator < (const Base & base) const {  
		return (strcmp (name, base) < 0) ? 1 : 0;  
	 }  

	 ostream & Write (ostream & stream) const {
		return stream << "name:  " << name
			<< "  Studentnum:  " << studentnum;
	}
};

/* hash function */
UCSDStudent :: operator long (void) const {  

	/* set a sum to hold the sum of each element */
	long sum = 0;  
    
	/* use for loop to calculate total hash code */
	for (long index = 0; name[index]; index++)  
		sum += name[index];  
    
	return sum;  
} 


int main (int argc, char * const * argv) {
	SymTab ST (5);
	char buffer[128];
	char command;
	long number;
	char option;

	/* initialize debug variable */
	HashTable::Set_Debug(0);

	 /* check command line options for debug display */
	 while ((option = getopt (argc, argv, "x")) != EOF) {

		 switch (option) {
			 case 'x': HashTable::Set_Debug(1);
				 break;
		 	}
	} 

	ST.Write (cout << "Initial Symbol Table:\n");
	while (cin) {
		command = NULL;		// reset command each time in loop
		cout << "Please enter a command:  ((i)nsert, (l)ookup, (w)rite):  ";
		cin >> command;

		switch (command) {
		case 'i':
			cout << "Please enter UCSD student name to insert:  ";
			cin >> buffer;	// formatted input

			cout << "Please enter UCSD student number:  ";
			cin >> number;

			// create student and place in symbol table
			if(!ST.Insert (new UCSDStudent (buffer, number))){

				ST.Write (cout << "\nFinal Symbol Table:\n");
				exit (0);
			}
			break;

		case 'l': {
			const Base * found;	// whether found or not

			cout << "Please enter UCSD student name to lookup:  ";
			cin >> buffer;	// formatted input

			UCSDStudent stu (buffer, 0);
			found = ST.Lookup (& stu);
			
			if (found)
				found->Write (cout << "Student found!!!\n") << "\n";
			else
				cout << "Student " << buffer << " not there!\n";
			}
			break;

		case 'w':
			ST.Write (cout << "The Symbol Table contains:\n");
		}
	}
	ST.Write (cout << "\nFinal Symbol Table:\n");
}

