/*******************************************************************************
 *                                                            Gang Yang
 *                                                            CSE 12, fall16
 *                                                            DUE 10-21
 *                                                            
 *                              Assignment 4
 * File name: stack.c
 * Description: In this assignment, I will develop a program that will
 * simulate a top-of-the-line calculator that will perform such advance
 * commands as addition,
 * subtractions,multiplication,division,exponentiation,and factorial
 *
 * ****************************************************************************/
#include <malloc.h>
#include <stdio.h>
#include "mylib.h"
#include "stack.h"

#define STACK_POINTER_INDEX (-1)        /* Index of last used space */
#define STACK_SIZE_INDEX (-2)           /* Index of size of the stack */
#define STACK_COUNT_INDEX (-3)          /* Index of which stack allocated */
#define STACK_OFFSET 3  /* offset from allocation to where user info begins */

/* catastrophic error messages */
static const char DELETE_NONEXIST[] = "Deleting a non-existent stack!!!\n";
static const char EMPTY_NONEXIST[] = "Emptying a non-existent stack!!!\n";
static const char INCOMING_NONEXIST[] = 
                        "Incoming parameter does not exist!!!\n";
static const char ISEMPTY_NONEXIST[] = 
                        "Isempty check from a non-existent stack!!!\n";
static const char ISFULL_NONEXIST[] = 
                        "Isfull check from a non-existent stack!!!\n";
static const char NUM_NONEXIST[] = 
                        "Num_elements check from a non-existent stack!!!\n";
static const char POP_NONEXIST[] = "Popping from a non-existent stack!!!\n";
static const char POP_EMPTY[] = "Popping from an empty stack!!!\n"; 
static const char PUSH_NONEXIST[] = "Pushing to a non-existent stack!!!\n";
static const char PUSH_FULL[] = "Pushing to a full stack!!!\n";
static const char TOP_NONEXIST[] = "Topping from a non-existent stack!!!\n";
static const char TOP_EMPTY[] = "Topping from an empty stack!!!\n";
static const char WRITE_NONEXIST_FILE[] = 
                        "Attempt to write using non-existent file pointer!!!\n";
static const char WRITE_NONEXIST_STACK[] = 
                        "Attempt to write to a non-existent stack!!!\n";

/* Debug messages. HEX messages used for negative numbers on the stack. */
static const char ALLOCATED[] = "[Stack %ld has been allocated]\n";
static const char DEALLOCATE[] = "[Stack %ld has been deallocated]\n";
static const char HEXPOP[] = "[Stack %ld - Popping 0x%lx]\n";
static const char HEXPUSH[] = "[Stack %ld - Pushing 0x%lx]\n";
static const char HEXTOP[] = "[Stack %ld - Topping 0x%lx]\n";
static const char POP[] = "[Stack %ld - Popping %ld]\n";
static const char PUSH[] = "[Stack %ld - Pushing %ld]\n";
static const char TOP[] = "[Stack %ld - Topping %ld]\n";

/* static variable allocation */
static int debug = FALSE; /* allocation of debug flag */
static int stack_counter = 0; /* number of stacks allocated so far */

/* Debug state methods */
void debug_off (void) {
        debug = FALSE;
}

void debug_on (void) {
        debug = TRUE;
}
 
/*---------------------------------------------------------------------------
Function Name:                delete_Stack
Purpose:                      This function deallocates all memory associated
                              with the stack and sets it pointer in the calling
			      functon to NULL
Description:                  This function first checks that the parameter of
                              spp is not a null pointer and that the pointer
			      it's pointing to is not a null pointer. Then the
			      function use free to deallocated the memory.
Input:                        **spp: double pointer to the stack that is 
                                     to be deleted
Output:                       if spp or *spp are NULL pointer, output error
                              message
			      if debug is on, output debug message.
Result:                       current stack is deleted
                              void functio, no return.
---------------------------------------------------------------------------*/
void delete_Stack (Stack ** spp) {
	/* check that the parameter of spp and the pointer 
	 * is pointing to is not a null pointer*/
        if (spp == NULL || *spp == NULL){
                fprintf(stderr, DELETE_NONEXIST);
        }
	/* calling free to deallocate memory*/
	/* (*spp)-STACK_OFFSET is memory*/
        free((*spp)-STACK_OFFSET);
	*spp = NULL;
	/* debug message*/
	if(debug == TRUE){
                fprintf(stderr,DEALLOCATE,(long)stack_counter);
	}
	/* subtract one number of stack*/
	stack_counter--;
    
}

/*---------------------------------------------------------------------------
Function Name:                empty_Stack
Purpose:                      Effectively empties the stack of all its elements 
Description:                  set the stack pointer to -1  
Input:                        *this_Stack: pointer to the stack
Output:                       if this_Stack is a null pointer, output error
                              message
Result:                       current stack is empty
                              void functio, no return.
---------------------------------------------------------------------------*/
void empty_Stack (Stack * this_Stack) {
	/* check if this_Stack is a null pointer*/
        if (this_Stack == NULL){
                fprintf(stderr,EMPTY_NONEXIST);
        }
        /* let the index of stack pointer become the inital value -1*/
        else{
                this_Stack[STACK_POINTER_INDEX] = -1;
        }
}

/*---------------------------------------------------------------------------
Function Name:                isempty_Stack 
Purpose:                      check if the stack is empty 
Description:                  returns true is this_Stack is empty, and false
                              if it is not.
Input:                        *this_Stack: pointer to the stack
Output:                       if this_Stack is a null pointer, output error
                              message
Result:                       return TRUE or FALSE.
---------------------------------------------------------------------------*/
long isempty_Stack (Stack * this_Stack) {
	/* check if the stack is NULL*/
        if (this_Stack == NULL){
                fprintf(stderr, ISEMPTY_NONEXIST);
        }
	/* if the index of stack pointer is -1 return true, else return false*/
        if (this_Stack[STACK_POINTER_INDEX] == -1){
                return TRUE;
        }
        else{
                return FALSE;
        }
}

/*---------------------------------------------------------------------------
Function Name:                isfull_Stack 
Purpose:                      check if the stack is full 
Description:                  returns true is this_Stack is full, and false
                              if it is not.
Input:                        *this_Stack: pointer to the stack
Output:                       if this_Stack is a null pointer, output error
                              message
Result:                       return TRUE or FALSE.
---------------------------------------------------------------------------*/
long isfull_Stack (Stack * this_Stack) {
	/* check if the stack is NULL*/
        if (this_Stack == NULL){
                fprintf(stderr, ISFULL_NONEXIST);
        }
        /* check if the index of stack pointer is equal to total number
        *  this_Stack could hold*/
        if (this_Stack[STACK_POINTER_INDEX] == this_Stack[STACK_SIZE_INDEX]-1){
                return TRUE;
        }
        else{
                return FALSE;
        }
}

/*---------------------------------------------------------------------------
Function Name:                new_Stack
Purpose:                      allocates and initializes a new Stack object
Description:                  this function allocates memory to hold
                              stacksize number of longs, initializes the
                              stack infrastructure 
Input:                        stacksize: type-unsigned long, should be
                              positive integer
Output:                       if debug is on, output debug message
Result:                       returns a pointer to the first storage space
                              in the stack.
---------------------------------------------------------------------------*/
Stack * new_Stack (unsigned long stacksize) {
        /* allocate */
        void * memory = malloc((STACK_OFFSET + stacksize)*sizeof(long));
        Stack * this_Stack = (Stack*)memory + STACK_OFFSET;
        /* initialize */
        this_Stack[STACK_POINTER_INDEX] = -1;
        this_Stack[STACK_SIZE_INDEX] = stacksize;
        this_Stack[STACK_COUNT_INDEX] = ++stack_counter;
        /* debug message */
        if (debug == TRUE){
                fprintf(stderr, ALLOCATED, this_Stack[STACK_COUNT_INDEX]);
        }
        return this_Stack;
}

/*---------------------------------------------------------------------------
Function Name:                num_elements
Purpose:                      this function returns the number of 
                              elements in this_Stack         
Description:                  this function returns the number of
                              elements in this_Stack
Input:                        *this_Stack: pointer to the stack
Output:                       if this_Stack is null, output error message
Result:                       returns a long repersenting number of elements
                              in this_Stack, if this_Stack == NULL, returns
                              FALSE
---------------------------------------------------------------------------*/
long num_elements (Stack * this_Stack) {
        /* check if this_Stack is NULL pointer */
        if (this_Stack == NULL){
                fprintf(stderr,NUM_NONEXIST);
	        return FALSE;
        }
        else{
                /* return the number of elements inside the stack */
                /* index of stack pointer plus one is the total number of 
		 * elements because the initial index is 0 */
                return (this_Stack[STACK_POINTER_INDEX]+1);
        }
    
}

/*---------------------------------------------------------------------------
Function Name:                pop
Purpose:                      this function removes an item from the top of
                              the stack and sends it back through the output 
                              parameter item.        
Description:                  this function first do error checks on the 
                              pointers, then check if the stack is empty, if
                              it is, output error message, if not, let long 
                              pointer be the last input element and remove the 
                              last input element.
Input:                        *this_Stack: pointer to the stack
                              *item: pointer to a long which will store the 
                                     popped item.
Output:                       if this_Stack is null, output error message
                              if item is null, output error message
                              if debug is on, output debug message
                              if this_Stack is empty, output error message
Result:                       Returns true upon success and false upon failure.
---------------------------------------------------------------------------*/
long pop (Stack * this_Stack, long * item) {
        /* check if this_Stack is null */
        if (this_Stack == NULL){
                fprintf(stderr,POP_NONEXIST);
	        return FALSE;
        }
        /* check if item is null */
        if (item == NULL){
                fprintf(stderr,INCOMING_NONEXIST);
                return FALSE;
        }
        /* check if this_Stack is empty */
        if (isempty_Stack(this_Stack) == FALSE){
                /* let *item be the last user input element */	
                *item = this_Stack[this_Stack[STACK_POINTER_INDEX]];
                /* remove the last element */
                this_Stack[STACK_POINTER_INDEX]--;
                /* debug message */
                if (debug == TRUE){
			/* check for the right debug message */
			if (*item < 0){
                                fprintf(stderr,HEXPOP,
				this_Stack[STACK_COUNT_INDEX],*item);
			}
			else {
                                fprintf(stderr,POP,
				this_Stack[STACK_COUNT_INDEX],*item);

			}
                }	
                return TRUE;
        }
        else{
                fprintf(stderr,POP_EMPTY);
	        return FALSE;
        }
}

/*---------------------------------------------------------------------------
Function Name:                push
Purpose:                      this function add item to the top of this_Stack
Description:                  this function has a local variable, first the
                              function checks if this_Stack is null, then it
                              checks if this_Stack is empty. if it is, output 
                              error message, if not, let last user input 
                              element equals to item. 
Input:                        *this_Stack: pointer to the stack
                              item: a long which will pushed on the stack 
Output:                       if this_Stack is null, output error message
                              if debug is on, output debug message
                              if this_Stack is empty, output error message
Result:                       Returns true upon success and false upon failure.
---------------------------------------------------------------------------*/
long push (Stack * this_Stack, long item) {
        /* set a local variable to hold the index of last stack pointer */
        long sp;
        /* check if this_Stack is null */
        if (this_Stack == NULL){
                fprintf(stderr,PUSH_NONEXIST);
	        return FALSE;
        }
        /* check if the stack is empty */
        if (isfull_Stack(this_Stack) == FALSE){
                /* let sp equal to the index of stack pointer that 
		 * we are pushing on*/
                sp = ++this_Stack[STACK_POINTER_INDEX];
                this_Stack[sp] = item;
                /* debug message */
                if (debug == TRUE){
			/* check for the right debug message */
			if (item < 0){
                                fprintf(stderr, HEXPUSH,
				this_Stack[STACK_COUNT_INDEX],item);
			}
			else {
                                fprintf(stderr, PUSH,
			        this_Stack[STACK_COUNT_INDEX],item);
			}
                }  
	        return TRUE;
        }
        else{
	        fprintf(stderr, PUSH_FULL);
                return FALSE;
        }
    
}

/*---------------------------------------------------------------------------
Function Name:                top
Purpose:                      this function send back the item on the top of
                              the stack through the output parameter item.
Description:                  this function first do error checks on the 
                              pointers, then check if the stack is empty, if
                              it is, output error message, if not, let long 
                              pointer be the last input element.
Input:                        *this_Stack: pointer to the stack
                              *item: pointer to a long which will store the 
                                     popped item.
Output:                       if this_Stack is null, output error message
                              if item is null, output error message
                              if debug is on, output debug message
                              if this_Stack is empty, output error message
Result:                       Returns true upon success and false upon failure.
---------------------------------------------------------------------------*/
long top (Stack * this_Stack, long * item) {
        /* check if this_Stack is null */
        if (this_Stack == NULL){
                fprintf(stderr,TOP_NONEXIST);
	        return FALSE;
        }
        /* check if item is null */
        if (item == NULL){
                fprintf(stderr,INCOMING_NONEXIST);
                return FALSE;
        }
        /* check if this_Stack if empty */
        if (isempty_Stack(this_Stack) == FALSE){
                /* let *item be the last user input element */		
                *item = this_Stack[this_Stack[STACK_POINTER_INDEX]];
                /* debug message */
                if (debug == TRUE){
			/* check for the right debug message */
			if (*item <0){
                                fprintf(stderr,HEXTOP,
				this_Stack[STACK_COUNT_INDEX],*item);
			}
			else {
                                fprintf(stderr,HEXTOP,
				this_Stack[STACK_COUNT_INDEX],*item);
                                
			}
                }	
                return TRUE;
        }
        else{
                fprintf(stderr,TOP_EMPTY);
	        return FALSE;
        }

}

FILE * write_Stack (Stack * this_Stack, FILE * stream) {

        long index = 0;         /* index into the stack */

        if (this_Stack == NULL) {
                fprintf (stderr, WRITE_NONEXIST_STACK);
                return stream;
        }

        if (stream == NULL) {
                fprintf (stderr, WRITE_NONEXIST_FILE);
                return stream;
        }
                
        if (stream == stderr)
                fprintf (stream, "Stack has %ld items in it.\n",
                        num_elements (this_Stack));

        for (index = STACK_COUNT_INDEX + STACK_OFFSET;
                index < num_elements (this_Stack); index++) {

                if (stream == stderr)
                        fprintf (stream, "Value on stack is |0x%lx|\n",
                                this_Stack[index]);
                else {
                        if (this_Stack[index] < 0)
                                fprintf (stream, "%c ",
                                        (char) this_Stack[index]);
                        else
                                fprintf (stream, "%ld ", this_Stack[index]);
                }
        }

        return stream;
}
