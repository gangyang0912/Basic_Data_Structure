/****************************************************************************

                                                        Gang Yang
                                                        CSE 12, fall 2016
                                                        10-7, 2016
                                Assignment Two

File Name:      hw2.c
Description:    This program reads strings and integers from the user,
                processes them, and prints them back to the user.  Program
                terminates when user enters ^D.  At termination, program
                outputs sizes of various types of C/C++ pre defined types.

****************************************************************************/

/* declare fputc/fgetc */
#include <stdio.h>
#include <getopt.h>

/* define some program-wide constants */
#define ASCII_ZERO '0'
#define COUNT ((long) (sizeof (long) << 1))
#define ERROR -1
#define FALSE 0
#define MAXLENGTH 80
#define OFFSET ('a' - 'A')
#define SPACE ' '
#define TRUE 1
/* max index of array*/
#define MAX 1024 
#define MAX_HEX 15
#define DECIMAL 10
#define HEX 16
/* 9 to input in digits array index */
#define NINE 9


/* define the keyword "NULL" as 0 */
#ifdef NULL
#undef NULL
#endif
#define NULL 0

/* declarations for functions defined in this file */
void baseout (long number, long base, FILE *stream);
void clrbuf (int);
long decin (void);
void decout (unsigned long, FILE *);
void digiterror (int, long *, const char *);
long getaline (char *, long);
void hexout (unsigned long, FILE *);
void newline (FILE *);
long writeline (const char *, FILE *);


/* array for input checking and for output */
const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* messages */
const char CAUSED_OVERFLOW[] =  " caused overflow!!!\n";
const char DIGIT_STRING[] = "digit ";
const char REENTER_NUMBER[] = "\nPlease reenter number: ";
const char OUT_OF_RANGE[] = " out of range!!!\n";

/* debug messages */
const char DEBUG_GETALINE[] =
        "[*DEBUG:  The length of the string just entered is ";
const char DEBUG_WRITELINE[] =
        "\n[*DEBUG:  The length of the string displayed is ";
static long debug_on = FALSE;

/*--------------------------------------------------------------------------
Function Name:         baseout.
Purpose:               Takes in a positive number and displays in a given base.
Description:           initializing an array to store each digit of the number
                       use % to get values then devide number by base.store all
                       the values in the array and the use a loop to display 
                       values backward.
                       give a special case for hexdecimal using if sentence.
                       
Input:                 number: any positive integer.
                       base any positive integer.
                       filestream stream stdout or stderr
Result:                values of number%base.
                       values of hexdecimal with leading 0.
--------------------------------------------------------------------------*/
void baseout (long number, long base, FILE * stream) {
        /*make a new array*/

        char a[MAX];  
        /*index to put in the array*/    
        long index = 0;          
        /*count for for loop*/
        long i;                   
        if(base == HEX){
                /*let first 8 numbers of array to be 0*/
                for(i = 0; i<=COUNT; i++){
                        a[i]=digits[0];
                }
                /* find out digits */
                while(number != 0){

                        a[index] = digits[number%base];
                        number = number/base;
                        index++;
                }
		/*give index a total hex number */
                while (index<MAX_HEX){
                        index++;
                }
                /*print out digit*/
                for(;index>=0;index--){
                        fputc(a[index],stream);
                }
        }
	/* normal case */
        else{
                 /*find out digit*/
                 do {
                         a[index] = digits[number%base];
                         number = number/base;
                         index ++;
                 } while(number != 0);
		 /* the last digit  is no needed*/
                 index--;
		 /* print out hte digits*/
                 while(index>=0){
                         fputc(a[index],stream);
                         index --;
                  }
        }

}


/*-------------------------------------------------------------------------- 
Function Name:          clrbuf 
Purpose:                When called, this function will clear stdin. 
Description:            This function checks to see if the incoming 
                        parameter is already '\n' indicating that stdin 
                        is already clear.  If stdin is already clear, this 
                        function does nothing.  Otherwise, this function 
                        calls "fgetc" in a loop until stdin is clear. 
Input:                  character:  the most recent character received from a 
                                previous call to fgetc. 
Result:                 stdin cleared.  Nothing returned. 
--------------------------------------------------------------------------*/  
void clrbuf (int character) {  
        char ch =(char) character;
	/* repeatedly calling fgetc until ch meet a new line*/
        while(ch != '\n') {
                ch = (char)fgetc(stdin);
	}	

}
/*--------------------------------------------------------------------------
Function Name:         writeline.
Purpose:               prints out a string.
Description:           using a loop and fputc to print out each character of 
                       message.
                       
Input:                 message: a NULL terminated character arrays.
                       stream: stdout or stderr
Result:                return the length of the message.
                       message is displayed .
--------------------------------------------------------------------------*/
long writeline (const char * message, FILE * stream) {
        long index = 0;
        /* new integer to count how many characters to be displayed*/
	long counter =0;
        /* print out each character in message using a while loop*/
        while(message[index] != 0) {
	        /* check when message reaches a null character*/
	        if (message[index] != '\0'){
                        fputc(message[index],stream);
	                counter ++;
	        }
                index ++;
		
        }
	/* debug message */
        if (debug_on) {
	        fprintf(stderr,"%s %ld %c \n",DEBUG_WRITELINE,counter,']');
	}
        return(--counter);
}
/*--------------------------------------------------------------------------
Function Name:          digiterror
Purpose:                This function handles erroneous user input.
Description:            This function reinitializes sum, displays and
                        error message to the user, and asks for fresh
                        input.
Input:                  character:  The character that began the problem.
                        sum:  A pointer to the sum to reinitialize.
                        message:  The message to display to the user.
Result:                 The message is displayed to the user.  sum is 0.
--------------------------------------------------------------------------*/
void digiterror (int character, long * sum, const char * message) {

	/* handle error */
	clrbuf (character);

	/* reset sum */
		*sum = 0;

	/* output error message */
	writeline (DIGIT_STRING, stderr);
	fputc (character, stderr);
	writeline (message, stderr);

	writeline (REENTER_NUMBER, stdout);
}



/*--------------------------------------------------------------------------
Function Name:          decin
Purpose:                This function accepts integer input from the user.
Description:            This function processes user input in a loop that ends
                        when the user enters either a valid number or EOF.
                        If EOF is entered, EOF is returned.  Otherwise each
                        character entered is checked to verify that it is
                        numeric.  Non-numeric input is identified, the user
                        is notified, reprompted, and the loop begins again.
                        Once the input is verified to be valid, a series
                        of multiplication by 10 and addition can take
                        place to convert the ASCII characters entered into
                        a numeric quantity.
Input:                  None.
Result:                 The number entered or EOF.
--------------------------------------------------------------------------*/
long decin (void) {
        long character = 0;
        long sum=0;
	/* temp to store the prior value of sum*/
	long temp=0;                              
	character = fgetc(stdin);
	/* using while loop to input decimal*/
        while (character != '\n'){
                /* check for EOF*/
	        if (character == EOF) {

	                return EOF;
	        }
                /* check for correct digits */
                /* if true, do sum algorithm */
	        if (character >= digits[0] && character <= digits[NINE]){
	                temp = sum;
                        sum = sum *DECIMAL;
                        sum += (character - ASCII_ZERO);
	                /* check if the current divided by 10 is equal to */ 
                        /* prior sum if true, continue take in digits */
		        if (sum/DECIMAL == temp) {
	                        character =fgetc(stdin);
	                }
		        /* if false, call digiterror and let sum equal to 0 */
		        else {
                                digiterror(character,&sum, CAUSED_OVERFLOW);
	                        character = fgetc(stdin);
                        }
                }
                /* if not correct input digit, call digiterror and reenter */
                else {
                        digiterror(character,&sum, OUT_OF_RANGE);
       	                character =fgetc(stdin);
                }
        }

        return sum;
}


/*--------------------------------------------------------------------------
Function Name:         decout.
Purpose:               takes in a positive number and displays it in decimal.
Description:           use the function baseout but the base is DECIMAL(10)
                       
Input:                 number: any positive integer.
                       filestream stream: stdout or stderr
Result:                each digit of the number.
                       no return value
--------------------------------------------------------------------------*/
void decout (unsigned long number, FILE * stream) {
        baseout(number,DECIMAL,stream);
}



/*--------------------------------------------------------------------------
Function Name:          getaline
Purpose:                This function will read a string from the user.
Description:            This function gets input from the user via
                        calls to fgetc up to some maximum number of
                        characters.  Input is terminated when either the
                        maximum number of characters are entered, or
                        a newline character is detected.  If the user
                        enters more characters than the maximum, clrbuf
                        is called to remove extra characters which are
                        ignored.  Since this is routine accepts input,
                        if EOF is detected EOF is passed back to the main
                        program.
Input:                  message:  the destination array where input is stored.
                        maxlength:  the maximum number of non-NULL characters
                                allowed in the string + 1 for the NULL char.
Result:                 User input is stored in message.
                        EOF is returned when the user enters ^D.
                        Otherwise, the length of the message is returned.
--------------------------------------------------------------------------*/
long getaline (char * message, long maxlength) {
        long character;
        long index = 0;
	/*loop that store each character input by user into array one by one*/
        do {
            character = fgetc(stdin);
	    /* check EOF*/
	    if (character == EOF) {
	        return EOF;
	    }
	    /* if the string reach maxlength, call clrbuf and get rid 
	       of the extra characters
	       end the loop*/
	    if (index == maxlength) {
                clrbuf(character);
	        break;
	    }
	    message[index] = (char)character;
            index ++;
        } while(character != '\n');
	/*store '\0' in the array after the last user entered character*/
        message[--index] = '\0';
	/*when the debug is on, print out dubug message*/
	if (debug_on) {
	    fprintf(stderr,"%s %ld %c \n",DEBUG_GETALINE,index,']');
        }
        return (index);
}


/*--------------------------------------------------------------------------
Function Name:         hexout
Purpose:               Prints a number in base 16 to the parameter FILE stream
Description:           Goal is achieved via delegating to the baseout function
Input:                 number:  the number to display
                       stream:  where to display, likely stdout or stderr
Result:                Number in base 16 is displayed.
                       No return value.
--------------------------------------------------------------------------*/
void hexout (unsigned long number, FILE * stream) {

        /* Output "0x" for hexidecimal. */
        writeline ("0x", stream);
        baseout (number, HEX, stream);
}

/*--------------------------------------------------------------------------
Function Name:         newline.
Purpose:               prints out a newline character.
Description:           use fputc to printout a new line
                       
Input:                 stream: stdout or stderr.
Result:                prints out a line.
                       no return.
--------------------------------------------------------------------------*/
void newline (FILE * stream) {
    fputc('\n',stream);
}



/*--------------------------------------------------------------------------
Function Name:          main
Description:            This function asks for input and displays output
Purpose:                This program asks the user to enter a string
                        and a number.  Computations are performed on the 
                        strings and numbers, and the results are displayed.
Description:            This function asks for input and displays output
                        in an infinite loop until EOF is detected.  Once EOF
                        is detected, the lengths of the types are displayed.
Input:                  None.
--------------------------------------------------------------------------*/
int main (int argc, char *const* argv) {

	long base;                  /* to hold output base */
	char buffer[MAXLENGTH];     /* to hold string */
	long number;                /* to hold number entered */
	long strlen;                /* length of string */

	long array[10];             /* to show user where memory is allocated */
	long * ap = array;	    /* to show user about addresses in memory */
	long ** app = &ap;	    /* to show user about addresses in memory */
	long * apx = &array[0];	    /* to show user about addresses in memory */
	char option;                /* the command line option */

	/* initialize debug states */
	debug_on = FALSE;

	/* check command line options for debug display */
	while ((option = getopt (argc, argv, "x")) != EOF) {
		switch (option) {
			case 'x': debug_on = TRUE; break;
		}
	}

	/* infinite loop until user enters ^D */
	while (1) {
		writeline ("\nPlease enter a string:  ", stdout);
		strlen = getaline (buffer, MAXLENGTH);
		newline (stdout);

		/* check for end of input */
		if (strlen == EOF)
			break;

		writeline ("The string is:  ", stdout);
		writeline (buffer, stdout);

		writeline ("\nIts length is ", stdout);
		decout (strlen, stdout);
		newline (stdout);

		writeline ("\nPlease enter a decimal number:  ", stdout);
		if ((number = decin ()) == EOF)
			break;

		writeline ("\nPlease enter an output base (2-36):  ", stdout);
		if ((base = decin ()) == EOF)
			break;

		writeline ("Number entered is:  ", stdout);
		decout (number, stdout);

		writeline ("\nAnd in hexidecimal is:  ", stdout);
		hexout (number, stdout);

		writeline ("\nAnd in base ", stdout);
		decout (base, stdout);
		writeline (" is:  ", stdout);
		baseout (number, base, stdout);

		writeline ("\nNumber entered multiplied by 8 is:  ", stdout);
		decout (number << 3, stdout);
		writeline ("\nAnd in hexidecimal is:  ", stdout);
		hexout (number << 3, stdout);

		newline (stdout);
	}

	writeline ("\nThe value of ap is:  ", stdout);
	decout ((long) ap, stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((long) ap, stdout);
	newline (stdout);

	writeline ("The value of app is:  ", stdout);
	decout ((long) app, stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((long) app, stdout);
	newline (stdout);

	writeline ("The value of apx is:  ", stdout);
	decout ((long) apx, stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((long) apx, stdout);
	newline (stdout);

	writeline ("The value of ap + 1 is:  ", stdout);
	decout ((long) (ap+1), stdout);
	writeline ("\nAnd in hexidecimal is:  ", stdout);
	hexout ((long) (ap+1), stdout);
	newline (stdout);

	writeline ("The address of array[0] is:  ", stdout);
	decout ((long) &array[0], stdout);
	newline (stdout);

	writeline ("The address of array[1] is:  ", stdout);
	decout ((long) &array[1], stdout);
	newline (stdout);

	writeline ("The size of a float is:  ", stdout);
	decout (sizeof (float), stdout);
	newline (stdout);

	writeline ("The size of a double is:  ", stdout);
	decout (sizeof (double), stdout);
	newline (stdout);

	writeline ("The size of a long double is:  ", stdout);
	decout (sizeof (long double), stdout);
	newline (stdout);

	writeline ("The size of a char is:  ", stdout);
	decout (sizeof (char), stdout);
	newline (stdout);

	writeline ("The size of an int is:  ", stdout);
	decout (sizeof (int), stdout);
	newline (stdout);

	writeline ("The size of a short is:  ", stdout);
	decout (sizeof (short), stdout);
	newline (stdout);

	writeline ("The size of a short int is:  ", stdout);
	decout (sizeof (short int), stdout);
	newline (stdout);

	writeline ("The size of a long is:  ", stdout);
	decout (sizeof (long), stdout);
	newline (stdout);

	writeline ("The size of a long int is:  ", stdout);
	decout (sizeof (long int), stdout);
	newline (stdout);

	writeline ("The size of a long long is:  ", stdout);
	decout (sizeof (long long), stdout);
	newline (stdout);

	writeline ("The size of a signed is:  ", stdout);
	decout (sizeof (signed), stdout);
	newline (stdout);

	writeline ("The size of a signed char is:  ", stdout);
	decout (sizeof (signed char), stdout);
	newline (stdout);

	writeline ("The size of a signed short is:  ", stdout);
	decout (sizeof (signed short), stdout);
	newline (stdout);

	writeline ("The size of a signed short int is:  ", stdout);
	decout (sizeof (signed short int), stdout);
	newline (stdout);

	writeline ("The size of a signed int is:  ", stdout);
	decout (sizeof (signed int), stdout);
	newline (stdout);

	writeline ("The size of a signed long is:  ", stdout);
	decout (sizeof (signed long), stdout);
	newline (stdout);

	writeline ("The size of a signed long int is:  ", stdout);
	decout (sizeof (signed long int), stdout);
	newline (stdout);

	writeline ("The size of a signed long long is:  ", stdout);
	decout (sizeof (signed long long), stdout);
	newline (stdout);

	writeline ("The size of an unsigned is:  ", stdout);
	decout (sizeof (unsigned), stdout);
	newline (stdout);

	writeline ("The size of an unsigned char is:  ", stdout);
	decout (sizeof (unsigned char), stdout);
	newline (stdout);

	writeline ("The size of an unsigned short is:  ", stdout);
	decout (sizeof (unsigned short), stdout);
	newline (stdout);

	writeline ("The size of an unsigned short int is:  ", stdout);
	decout (sizeof (unsigned short int), stdout);
	newline (stdout);

	writeline ("The size of an unsigned int is:  ", stdout);
	decout (sizeof (unsigned int), stdout);
	newline (stdout);

	writeline ("The size of an unsigned long is:  ", stdout);
	decout (sizeof (unsigned long), stdout);
	newline (stdout);

	writeline ("The size of an unsigned long int is:  ", stdout);
	decout (sizeof (unsigned long int), stdout);
	newline (stdout);

	writeline ("The size of an unsigned long long is:  ", stdout);
	decout (sizeof (unsigned long long), stdout);
	newline (stdout);

	writeline ("The size of a void pointer is:  ", stdout);
	decout (sizeof (void *), stdout);
	newline (stdout);

	writeline ("The size of a character pointer is:  ", stdout);
	decout (sizeof (char *), stdout);
	newline (stdout);

	writeline ("The size of an int pointer is:  ", stdout);
	decout (sizeof (int *), stdout);
	newline (stdout);

	writeline ("The size of a long pointer is:  ", stdout);
	decout (sizeof (long *), stdout);
	newline (stdout);

	writeline ("The size of a float pointer is:  ", stdout);
	decout (sizeof (float *), stdout);
	newline (stdout);

	writeline ("The size of a double pointer is:  ", stdout);
	decout (sizeof (double *), stdout);
	newline (stdout);

	writeline ("The size of a long double pointer is:  ", stdout);
	decout (sizeof (long double *), stdout);
	newline (stdout);

	newline (stdout);

	return 0;
}
