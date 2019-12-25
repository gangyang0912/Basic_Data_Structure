/****************************************************************************

                                                Gang Yang
                                                CSE 12, fall16
                                                11-04
                                                
                              Assignment 6

File Name:      Driver.java
Description:    This program let us build a hash table to hold the students'
                information. In the assignment, we are to implement a Symbol 
                Table to allow variable assignment to the calculator. 
                we are also to write the member functions for the UCSDStudent 
                class as part of the Driver.java file and the Driver.c file 
                used to test our symbol table.

****************************************************************************/
import java.io.*;
/* Class Header: UCSDStudent 
 * Description:  this class holds basic information of each student and 
                 functions we will use later.
 * Functions:    public UCSDStudent(String buffer, long number)
 *               public UCSDStudent(UCSDStudnet stu)
 *               public String getName()
 *               public boolean equals (Object object)
 *               public boolean isLessThan(Base base)
 *               public String toStrig()
 *               public int hashCode() 
 */
class UCSDStudent extends Base {
        private String name;
        private long studentnum;

        /* Fucntion name : UCSDStudent 
         * purpose:        initialize name and studentnum
         * parameter:      buffer - String - input String of 
         *                                 student's name
         *                 number - long - input student's number
         * return:         constructor, no return 
         */
        public UCSDStudent(String buffer, long number){
                name = buffer;
                studentnum = number;
        }

        /* Fucntion name : getName
         * purpose:        get the name
         * parameter:      
         * return:         return name type String
         */
        public String getName () {  
                return name;  
        }  

        /* Fucntion name : equals
         * purpose:        check if item in the hashtable
         *                 equals to the input element
         * parameter:      object - Object 
         * return:         return true or false type boolean
         */
        public boolean equals (Object object) {  
                Base base = (Base) object;  
                return name.equals (base.getName ());  
        }  

        /* Fucntion name : isLessThan
         * purpose:        check if item in the hashtable
         *                 is less than the input element
         * parameter:      base - base 
         * return:         return true or false type boolean
         */
        public boolean isLessThan (Base base) {  
                return (name.compareTo (base.getName ()) < 0) ? true : false;  
        }  

        /* Fucntion name : toString
         * purpose:        output the name and studentnum
         * parameter:      
         * return:         return String
         */
        public String toString () {  
                return "name:  " + name + "  Studentnum:  " + studentnum; 
        }  
        
        /* Fucntion name : haseCode
         * purpose:        convert the input element to ascii number
         * parameter:       
         * return:         return the total ascii number of the element 
         *                 type int
         */
        public int hashCode () {  
                int retval = 0;  
                int index = 0;  
                while (index != name.length ()) {  
                        retval += name.charAt (index);  
                        index ++;  
                }  
                return retval;  
        }    
}

public class Driver {
        private static final short NULL = 0;

        public static void main (String [] args) {
                /* initialize debug states */
                HashTable.setDebugOff();

                /* check command line options */
                for (int index = 0; index < args.length; ++index) {
                        if (args[index].equals("-x"))
                                HashTable.setDebugOn();
                }

                /* The real start of the code */
                SymTab symtab = new SymTab (5);
                String buffer = null;
                char command;
                long number = 0;

                System.out.print ("Initial Symbol Table:\n" + symtab);

                while (true) {
                        command = 0;    // reset command each time in loop
                        System.out.print ("Please enter a command:  "
                                + "((i)nsert, (l)ookup, (w)rite):  ");

                        try {
                        command = MyLib.getchar ();
                        MyLib.clrbuf (command); // get rid of return

                        switch (command) {
                        case 'i':
                                System.out.print (
                                "Please enter UCSD Student name to insert:  ");
                                buffer = MyLib.getline ();// formatted input

                                System.out.print (
                                        "Please enter UCSD Student number:  ");

                                number = MyLib.decin ();
                                MyLib.clrbuf (command); // get rid of return

                                // create Student and place in symbol table
                                if(!symtab.insert (
                                        new UCSDStudent (buffer, number))){

                                        System.out.print ("\nFinal Symbol "
                                                        + "Table:\n" + symtab);
                                        System.exit(0);
                                }
                                break;

                        case 'l': {
                                Base found;     // whether found or not

                                System.out.print (
                                "Please enter UCSD Student name to lookup:  ");

                                buffer = MyLib.getline ();// formatted input

                                UCSDStudent stu = new UCSDStudent (buffer, 0);
                                found = symtab.lookup (stu);
                                
                                if (found != null) {
                                        System.out.println ("Student found!!!");
                                        System.out.println (found);
                                }
                                else
                                        System.out.println ("Student " + buffer
                                                + " not there!");
                                }
                                break;

                        case 'w':
                                System.out.print (
                                    "The Symbol Table contains:\n" + symtab);
                        }
                        }
                        catch (EOFException eof) {
                                break;
                        }
                }

                System.out.print ("\nFinal Symbol Table:\n" + symtab);
        }
}
