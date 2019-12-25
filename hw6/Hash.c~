/****************************************************************************

                                                Gang Yang
                                                CSE 12, fall16
                                                11-04
                                                
                              Assignment 6

File Name:      Hash.c
Description:    This program let us build a hash table to hold the students'
                information. In the assignment, we are to implement a Symbol 
                Table to allow variable assignment to the calculator. 
                we are also to write the member functions for the UCSDStudent 
                class as part of the Driver.java file and the Driver.c file 
                used to test our symbol table.

****************************************************************************/

#include <cstdlib>
#include <string.h>
#include "Hash.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

using namespace std;

/* debug messages */
static const char DEBUG_ALLOCATE[] = " - Allocated]\n";
static const char DEBUG_INSERT[] = " - Insert]\n";
static const char DEBUG_LOCATE[] = " - Locate]\n";
static const char DEBUG_LOOKUP[] = " - Lookup]\n";
static const char FULL[] = " is full...aborting...]\n";
static const char HASH[] = "[Hash Table ";
static const char HASH_VAL[] = "[Hash value is: ";
static const char INSERT_BUMP[] = "[bumping to next location...]\n";
static const char PROCESSING[] = "[Processing ";
static const char TRYING[] = "[Trying index ";


long HashTable :: debug = 0;
int HashTable :: counter = 0;


void HashTable :: Set_Debug (long option)

/***************************************************************************
% Routine Name : HashTable :: Set_Debug (public)
% File :         Hash.c
% 
% Description :  This function sets debug mode on or off
%
% Parameters descriptions :
% 
% name               description
% option 			 hold option of true or false. 
% ------------------ ------------------------------------------------------
% option             true should set debug mode on, false should set debug
%                    mode off.
***************************************************************************/

{		         
                /* set check if option is true or not */
                if (option == TRUE){
        	            debug = TRUE;
                }
                else{
        	            debug = FALSE;
                }
}


HashTable :: HashTable (long sz) : size (sz),
        table_count(++counter), occupancy (0), table (new Base *[sz])
/***************************************************************************
% Routine Name : HashTable :: HashTable (public)
% File :         Hash.c
% 
% Description :  This function allocates an initializes the memory
%                associated with a hash table.
%
% Parameters descriptions :
% 
% name               description
% sz                 the size of the table
% ------------------ ------------------------------------------------------
% size               The number of elements for the table...MUST BE PRIME!!!
***************************************************************************/

{
                /* initialize all table elements */
                /* create a count to count until it reaches the size of the
		 * table */
    	        long count = 0;

                /* while loop to set all index of table to NULL */
    	        while (count < sz){

                        /* set each index of the table to NULL */
    		        table[count] = NULL;

                        /* increase the count */
    		        count++;
    	        }

		/* debug message */
		if (debug){
			cerr<<HASH<<table_count<<DEBUG_ALLOCATE;
		}

}	/* end: HashTable */


HashTable :: ~HashTable (void)
/***************************************************************************
% Routine Name : HashTable :: ~HashTable  (public)
% File :         Hash.c
% 
% Description :  deallocates memory associated with the Hash Table.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{
                /* create a new value to count until it reaches the size of the 
                table */
                long count = 0;

	        /* call function to delete individual elements */
                while (count < size){

                        /* call delete function to delete each element in 
                        the table */
                        delete(table[count]);

                        /* set each element in the table to NULL */
                        table[count] = NULL;

                        /* increase the count */
                        count++;
	        }

	        /* delete table itself */
                delete[] table;

                table = NULL;
                --counter;
}	/* end: ~HashTable */


long HashTable :: Insert (Base * element, long recursiveCall)
/***************************************************************************
% Routine Name : HashTable :: Insert (public)
% File :         Hash.c
% 
% Description : This function will insert the element in the hash table.
%		If the element cannot be inserted, false will be returned.
                If the element can be inserted, the element is inserted and 
		true is returned. Duplicate insertions will cause the existing
		element to be deleted, and the duplicate element to take its
		place.
%
% Parameters descriptions :
%  
% name               description
% element            type - Base* complete elements to insert
% recursiveCall      type - long  represent whether or not this function 
                                  was called recursively
% ------------------ ------------------------------------------------------
% element            The element to insert.
% recursiveCall      Whether the call to this function is recursive or not.
% <return>           1 or 0 indicating success or failure of insertion
***************************************************************************/

{
	            /* create a new value to hold the current value if table */
                Base * currentValue;

                /* create a new value to hold the value we located */
                const Base * located;

                /* debug message */
                if (debug){
                	cerr<<HASH<<table_count<<DEBUG_INSERT;
                }

                /* check fo we need recursive or not */
                if (recursiveCall == FALSE){
                        index = -1;
                }

                /* call locate function to find out the proper position 
                for the element */
                located = Locate(element);

                /* check if the table is full */
                if (occupancy == size){
                		
                        /* debug message */
                        if (debug){
                        	    cerr<<HASH<<table_count<<FULL;
                        }
                        return FALSE;
                }

                /* when the element we located is equal to null */
                else if (located == NULL){

                        /* if the table has nothing at the index */
                        if (table[index] == NULL){

                                /* set the table at the index to element */
				table[index] = element;

                                /* increase the occupancy */
                                ++occupancy;                                
                        }

                        /* if the table has element at the index */
                        else {

                                /* debug message */
                                if (debug){
                                		cerr<<INSERT_BUMP;
                                }

                                /* get the current value of the table at the
                                index */
                                currentValue = table[index];

                                /* let the table at the index be the element */
                                table[index] = element;

                                /* do recursion to insert the current value back
                                to the table */
                                Insert(currentValue,TRUE);
                        }
                }

                /* check the element we located is equal to the new input
                element */
                else if (located == element){
                        table[index] = element;
                }
                return TRUE;
}


const Base * HashTable :: Locate (const Base * element) const
/***************************************************************************
% Routine Name : HashTable :: Locate (private)
% File :         Hash.c
% 
% Description : This function will locate the location in the
                table for the insert or lookup.
%
% Parameters descriptions :
%  
% name               description
% element            type - const Base* complete and incomplete elements 
%                                       depending on whether it's called 
%                                       from insert or lookup.
% ------------------ ------------------------------------------------------
% element            The element needing a location
% <return>           item found, or null if not found

***************************************************************************/

{
                /* translate the key into a numeric value that can be used to 
                locate the index into the array where object is to be stored */
                long acsii_Sum = *element;

                /* create a value to hold the table size */
                long table_Size = size;

                /* location in the table to store a student */
                long current_location = acsii_Sum % table_Size;

                /* if the current location if full, find out the next location 
		 * by using increment */
                long increment = (acsii_Sum % (table_Size - 1)) + 1;

                /* check if we started recursion yet,
                if not, let index be the current location */
                if (index == -1){
                        index = current_location;
                }

                /* if we have already started recursion, 
                increase index to the next one if recursive */
                else{
                        index = (index+increment)%table_Size;
                }

                /* debug messages */
                if (debug){
			cerr<<HASH<<table_count<<DEBUG_LOCATE;
			cerr<<PROCESSING<<(const char*)(*element)<<"]\n";
			cerr<<HASH_VAL<<acsii_Sum<<"]\n";
			cerr<<TRYING<<index<<"]\n";
                }      

                /* the function stops when it finds an empty index */
                while (table[index] != NULL){

                        /* function stops when it finds an occupied index 
                        that is less than the current element */
                        if (*(table[index])<*element){
                                return NULL;
                        }

                        /* function stops when it finds the same item
			 * at an index */
                        if (*element == *(table[index])){
                                return table[index];
                        }

                        /* increase the index */
                        index = (index + increment) % table_Size;

                        /*debug message*/
                        if (debug){
                        		cerr<<TRYING<<index<<"]\n";
                        }

                        /* if we have looped the whole table and return back
			 * to the beginning location, stop */
                        if (index == current_location){
                                if (debug){
                                		cerr<<HASH<<table_count<<FULL;
                                }
                                return NULL;
                        }
                }

                /* if the item at the index is empty, return null */
                return NULL;
}


const Base * HashTable :: Lookup (const Base * element) const
/***************************************************************************
% Routine Name : HashTable :: Lookup (public)
% File :         Hash.c
% 
% Description : This function will lookup the element in the hash table.  If
%               found a pointer to the element is returned.  If the element
%               is not found, NULL will be returned to the user.
%
% Parameters descriptions :
%  
% name               description
% element            type - const Base*  incomplete elements (name is 
                                         present but number is missing) to 
                                         look up.
% ------------------ ------------------------------------------------------
% element            The element to insert or to lookup.
% <return>           A pointer to the element if found, else NULL
***************************************************************************/

{
                /* create a new value to hold the value we are locating */
                const Base * located;

                /* debug message */
                if (debug){
                        cerr<<HASH<<table_count<<DEBUG_LOOKUP;
                }

                /* set the index to be -1 in order to search
                from the beginning */
                index = -1;

                /* create a new value to hold the value we located */
                located = Locate(element);

                /* if there is a match, return that value*/
                if (located != NULL){
                        return table[index];
                }
                
                /* if there is nothing matches, return null */
                else {
                        return NULL;
                }
}


ostream & HashTable :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : HashTable :: Write (public)
% File :         hash.c
% 
% Description : This funtion will output the contents of the hash table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/

{
	stream << "Hash Table " << table_count << ":\n"
		<< "size is " << size << " elements, "
		<< "occupancy is " << occupancy << " elements.\n";

	/* go through all table elements */
	for (long index = 0; index < size; index++)
		if (table[index])
			table[index]->Write(stream << "at index "
			<< index << ":  ") << "\n";
	return stream;
}	/* end: Write */

