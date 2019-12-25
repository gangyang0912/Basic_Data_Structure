/*
 *--------------------------------------------------------------------------
                                                             Crystal Kwok
 * ------------------------------------------------------------------------
 *  File: HashTable.java
 *  Description: implement a Symbol Table with multiple functions to allow 
 *  variable assignment to the calculator
 *  -------------------------------------------------------------------------
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
        private static final String TRYING = "[Trying index ";

        
        /*
         * Sets debug off by setting it to false
         *
         * @no param
         */
        public static void setDebugOff () {
            debug= false;   
        }       

        /*
         * Sets debug on by setting it to true
         *
         * @no param
         */
        public static void setDebugOn () {
            debug=true;
        }       
        
        /*
         * Allocates and initializes the memory associated with a hash
         * table.  Sets the size of the hash table, sets the number of
         * items in the hash table, and increments the table count and 
         * the total number of tables.
         *
         * @param  sz   size of the hash table
         */
        public HashTable (int sz){
            /*set the global variable size to the size set when 
             * the user makes a new hash table*/
            size=sz; 
            /*initalize and allocate the table based on the size*/
            table=new Base[size];

            occupancy=0;   /*there are no elements in the table now*/
            
            /*increment the table count*/
            tableCount++;

            /*increment the total number of table count*/
            counter++;
            
            /*debug statement*/
            if (debug){
                System.err.print(HASH + tableCount + DEBUG_ALLOCATE);
            }
        }

        /*
         * Performs insertion into the tabble via delegation to the
         * private insert method.
         *
         * @param   element     Base/elemnt to insert
         * @return  a call to the other insert function with no 
         *          recursive call.
         */
        public boolean insert (Base element) {
                return insert (element, false);
        }

        /*
         * Inserts the element in the hash table.
         * If the element cannot be inserted, false will be returned.  
         * If the element can be inserted, the element is inserted and true is
         * returned. Duplicate insertions will cause the existing element
         * to be deleted, and the duplicate element to take its place.
         *
         * @param   element         element (which is a type of Base) to be 
         *                          inserted or looked up
         * @param   recursiveCall   whether the call to this function is 
         *                          recursive of not.
         * @return  true or false based on success or failure of insertion
         */
        private boolean insert (Base element, boolean recursiveCall) {
            /*debug statement*/
            if (debug)
                System.err.print(HASH + tableCount + DEBUG_INSERT);

            /*if it is not recursive, which means start from the beginning*/
            if (recursiveCall==false)
                index=-1;   /*start at the beginning by setting index to -1*/

            /*create base to hold the return value after locating the element
             * to be inserted*/
            Base check= locate(element);     

            /* if the table is full, return false*/
            if (occupancy==size){
                /*debug message*/
                if (debug)
                    System.err.print(HASH + tableCount + FULL);
                
                return false;
            }

            /*if the base from locate is equal to element, which means
             * there is a matching element*/
            else if (check== element){
                /*set the base in the table to the element & return true*/    
                table[index]= element;
                return true;
            }
  
            /*if the return from locate is null, or is just not equal to 
             * element*/
            else if (check==null){
                /*if the base at the index in the table is not empty*/
                if (table[index]!=null){
                    /*debug message*/
                    if (debug)
                        System.err.print(INSERT_BUMP);
                    
                    /*store the original base that was already in the table
                     * in a variable*/  
                    Base originalValue= table[index];
                    /*set the base at the index of the table to the element
                     * we want to insert*/
                    table[index]= element;

                    /*recurse the base that was originally in the table*/
                    insert(originalValue, true);
                    
                    /*return true if successful insertion*/
                    return true;
                }

                /*if the base at the index in the table is empty*/
                else {
                    
                    /*put the element we want to insert into the table
                     * at the index*/               
                    table[index]=element;
                    /*increment the number of elements in the table*/
                    ++occupancy;
                    /*return true if successful insertion*/
                    return true;
                }
            }
            /* if what is returned from locate is not null, and say
             * it was a successful insertion*/ 
            return true;  
        }

        /*
         * This function will locate the location in the table for the insert
         * or lookup.
         *
         * @param   element, that needs a location
         * @return  item found, or null if not found
         */
        private Base locate (Base element) {
            
            /*get the total ascii value of the element the user wishes to 
             * locate*/
            int numeric_attribute= element.hashCode();
            /*set a variable to hold the table size*/
            int table_size= size;  
            /*set the initial location to start checking to the ascii value
             * mod table size*/
            int initial_location= numeric_attribute % table_size;
            /*figure out the next index if initial location is full by using
             * incremenet*/
            int increment= (numeric_attribute % (table_size-1))+1;
            
            /*debug message*/
            if (debug)
                System.err.print(HASH + tableCount + DEBUG_LOCATE);
                    
            /*if it will be recursive, set the index to the next one with 
             * increment*/
            if (index != -1)
                index= (index+increment)% table_size;
            
            /*if it will not be recursive, set the index to the first 
             * location*/         
            else 
                index= initial_location;
            
            /*debug message*/
            if (debug){
                System.err.print(PROCESSING + element.getName() + "]\n");  
                System.err.print(HASH_VAL + numeric_attribute + "]\n");
                System.err.print(TRYING + index + "]\n");
            }
            
            /*if at the index of the table is empty*/
            while (table[index] !=null)
            {
                /*if the base at the index is equals to the element in
                 * question*/
                if ((table[index]).equals(element))
                    return table[index];    /*return the element*/
            
                /*if the base at the index is less than the element 
                 * in question, then return null*/
                if (table[index].isLessThan(element))
                    return null;
                
                /*increment the index*/
                index= (index+increment) % table_size;
                
                /*debug message*/
                if (debug)
                    System.err.print(TRYING + index + "]\n");
                
                /*if the entire table has been looped through and back to
                 * where it's started, return null*/    
                if (index== initial_location){
                    /*debug message*/
                    if (debug)
                        System.err.print(HASH + tableCount + FULL);
                    
                    return null;
                }
            }
            /*if the index at the table is empty, return null*/
            return null;        
        }

        /*
         * This function will lookup the element in the hash table.  If found
         * a pointer to the elemnt is returned.  If the element is not found,
         * NULL will be returned to the user.
         *
         * @param   element: the element to lookup in the table 
         * @return  return null if not found, return the element if found
         */
        public Base lookup (Base element) {
            /*set the index back to -1 to restart for locate*/
            index=-1;
            /*debug messages*/
            if (debug){
                System.err.print(HASH + tableCount + DEBUG_LOOKUP);
            }
            
            /*use locate to move the index to the appropriate place*/  
            Base check= locate(element);
            
            /*if the value from locate is null, then it is not found*/
            if (check==null){
                return null;
            }

            /*if the value from locate is not null, then it is found*/
            else {
                return table[index];
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