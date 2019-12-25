/****************************************************************************

                                                Gang Yang
                                                CSE 12, fall16
                                                11-04
                                                
                              Assignment 6

File Name:      HashTable.java
Description:    This program let us build a hash table to hold the students'
                information. In the assignment, we are to implement a Symbol 
                Table to allow variable assignment to the calculator. 
                we are also to write the member functions for the UCSDStudent 
                class as part of the Driver.java file and the Driver.c file 
                used to test our symbol table.

****************************************************************************/

/**
 * Class Header: HashTable.java
 * Functions: public static void setDebugOn ()
 *            public static void setDebugOff ()
 *            public HashTable (int sz)
 *            private boolean insert (Base element, boolean recursiveCall)
 *            private Base locate (Base element)
 *            public Base lookup (Base element)
 *
 * @author Tracker Wonderdog (cs12xbd)
 */ 
public class HashTable extends Base {

        /* counters, flags and constants */
        private static int counter = 0;         // number of HashTables so far
        private static boolean debug;           // allocation of debug states
        protected static final short NULL = 0;  // in case you want to use NULL

        /* data fields */
        private long occupancy;         // number of items stored in table
        private int size;               // size of hash table
        private Base table[];   // the Hash Table itself ==> array of Base
        private int tableCount; // which hash table it is 

        /* initialized by Locate function */
        private int index;      // last location checked in hash table


        /* debug messages */
        private static final String DEBUG_ALLOCATE = " - Allocated]\n";
        private static final String DEBUG_INSERT = " - Insert]\n";
        private static final String DEBUG_LOCATE = " - Locate]\n";
        private static final String DEBUG_LOOKUP = " - Lookup]\n";
        private static final String FULL = " is full...aborting...]\n";
        private static final String HASH = "[Hash Table ";
        private static final String HASH_VAL = "[Hash value is: ";
        private static final String INSERT_BUMP = 
                                        "[bumping to next location...]\n";
        private static final String PROCESSING = "[Processing "; 
        private static final String TRYING = "[Trying index "; ; 

        /**
         * Turns off debugging for this HashTable
         */
        public static void setDebugOff () {

                /* set debug to false */
                debug = false;
        }       

        /**
         * Turns on debugging for this HashTable
         */
        public static void setDebugOn () {

                /* set debug to false */
                debug = true;
        }       
        
        /**
         * Allocates and initializes the memory associated with a hash
         * table.set size to sz, set table to a new Base array, set 
         * occupancy to 0, increase counter and tableCount
         *
         * @param  sz   any positive prime to be the size of the table
         */
        public HashTable (int sz) {

                /* set the size to be the sz user inputted */
                size = sz;

                /* initalize the table with the size */
                table = new Base[size];

                /* elements in the table */
                occupancy = 0;

                /* how much table we have already initalized */
                counter++;

                /* increase the table counter in order to find out which
		 * table we are at*/
                tableCount ++;

                /* debug message */
                if (debug){
                        System.err.print(HASH + tableCount + DEBUG_ALLOCATE);
                }
        }

        /**
         * Performs insertion into the tabble via delegation to the
         * private insert method.
         *
         * @param   element        complete elements to insert
         * @return  return a insert funcion with element and 
         *          recursiveCall of false
         */
        public boolean insert (Base element) {
                return insert (element, false);
        }

        /**
         * Inserts the element in the hash table.
         * If the element cannot be inserted, false will be returned.  
         * If the element can be inserted, the element is inserted and true is
         * returned. Duplicate insertions will cause the existing element
         * to be deleted, and the duplicate element to take its place.
         *
         * @param   element        complete elements to insert
         * @param   recursiveCall  whether or not this function was 
         *                         called recursively
         * @return  return true or false to represent if the insert is sucessful
         *          or fail
         */
        private boolean insert (Base element, boolean recursiveCall) {

                /* create a new value to hold the current value if table */
                Base currentValue;

                /* create a new value to hold the value we located */
                Base located;

                /* debug message */
                if (debug){
                        System.err.print(HASH + tableCount + DEBUG_INSERT);
                }

                /* check fo we need recursive or not */
                if (recursiveCall == false){
                        index = -1;
                }

                /* call locate function to find out the proper position 
                for the element */
                located = locate(element);

                /* check if the table is full */
                if (occupancy == size){

                        /* debug message */
                        if (debug){
                                System.err.print(HASH + tableCount + FULL);
                        }
                        return false;
                }

                /* when the element we located is equal to null */
                else if (located == null){

                        /* if the table has nothing at the index */
                        if (table[index] == null){

                                /* set the table at the index to element */
				                table[index] = element;

                                /* increase the occupancy */
                                ++occupancy;                                
                        }

                        /* if the table has element at the index */
                        else {

                                /* debug message */
                                if (debug){
                                        System.err.print(INSERT_BUMP);
                                }

                                /* get the current value of the table at the
                                index */
                                currentValue = table[index];

                                /* let the table at the index be the element */
                                table[index] = element;

                                /* do recursion to insert the current value back
                                to the table */
                                insert(currentValue,true);
                        }
                }
                /* check the element we located is equal to the new input
                element */
                else if (located == element){
                        table[index] = element;
                }
                return true;
        }

        /**
         * Locates the index in the table where the insertion is 
         * to be performed, an item is found, or an item is determined 
         * not to be there. Sets the variable index to the last location 
         * checked; it will be used by insert and lookup. Returns the item 
         * if an item with matching name is found. Otherwise, return null. 
         * Loops stops when encountering a null table location or when 
         * encountering an item that is smaller than the parameter item.
         *
         * @param   element  complete and incomplete elements depending 
         *                   on whether it's called from insert or lookup
         * @return  Returns the item if an item with matching name is found.
         *          Otherwise, return null.
         */
        private Base locate (Base element) {

                /* translate the key into a numeric value that can be used to 
                locate the index into the array where object is to be stored */
                int acsii_Sum = element.hashCode(); 

                /* create a value to hold the table size */
                int table_Size = size;

                /* location in the table to store a student */
                int current_location = acsii_Sum % table_Size;

                /* if the current location if full, find out the next location 
		 * by using increment */
                int increment = (acsii_Sum % (table_Size - 1)) + 1;

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
                        System.err.print(HASH + tableCount + DEBUG_LOCATE);
                        System.err.print(PROCESSING+element.getName() + "]\n");
                        System.err.print(HASH_VAL + acsii_Sum + "]\n");
                        System.err.print(TRYING + index + "]\n");
                }      

                /* the function stops when it finds an empty index */
                while (table[index] != null){

                        /* function stops when it finds the
			 * same item at an index */
                        if (table[index].equals(element)){
                                return table[index];
                        }

                        /* function stops when it finds an occupied index 
                        that is less than the current element */
                        if (table[index].isLessThan(element)){
                                return null;
                        }

                        /* increase the index */
                        index = (index + increment) % table_Size;

                        /*debug message*/
                        if (debug){
                                System.err.print(TRYING + index + "]\n");
                        }

                        /* if we have looped the whole table and return back 
			 * to the beginning location, stop */
                        if (index == current_location){
                                if (debug){
                                        System.err.print(HASH+tableCount+FULL);
                                }
                                return null;
                        }
                }

                /* if the item at the index is empty, return null */
                return null;
        }

        /**
         * Looks up the element in the hash table. Returns pointer 
         * to the element if found, null otherwise.
         *
         * @param   element   incomplete elements (name is 
         *                    present but number is missing) to look up
         * @return  Returns pointer to the element if found, null otherwise.
         */
        public Base lookup (Base element) {

                /* create a new value to hold the value we located */
                Base located;

                /* debug message */
                if (debug){
                        System.err.print(HASH + tableCount +DEBUG_LOOKUP);
                }

                /* set the index to be -1 in order to search
                from the beginning */
		        index = -1;

                /* create a new value to hold the value we located */
		        located = locate(element);

                /* if there is a match, return that value*/
                if (located != null){
                        return table[index];
                }
                
                /* if there is nothing matches, return null */
                else {
                        return null;
                }
        }

        /**
         * Creates a string representation of the hash table. The method 
         * traverses the entire table, adding elements one by one
         * according to their index in the table. 
         *
         * @return  String representation of hash table
         */
        public String toString () {

                String string = "Hash Table " + tableCount + ":\n";
                string += "size is " + size + " elements, "; 
                string += "occupancy is " + occupancy + " elements.\n";

                /* go through all table elements */
                for (int index = 0; index < size; index++) {

                        if (table[index] != null) {
                                string += "at index " + index + ":  ";
                                string += "" + table[index] + "\n"; 
                        }
                }

                return string;
        }
}
