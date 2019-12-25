/****************************************************************************

                                                        Gang Yang
                                                        CSE 12, fall 2016
                                                        10-29, 2016
                                                        
                                Assignment Five

File Name:      list.c
Description:    In this assignment, we are going to create a polymorphic 
                generic container based on a linked-list data structure.

****************************************************************************/
/* 
1. end:          (Node *) 0x6040f0
2. Node 1 data: (void *) 0x604050
3. Node 1 pre:  (struct Node *) 0x6040f0
4. Node 1 next: (struct Node *) 0x6040b0
5. Node 2 data: (void *) 0x604090
6. Node 2 pre:  (struct Node *) 0x604070
7. Node 2 next: (struct Node *) 0x6040f0
8. Node 3 data: (void *) 0x6040d0
9. Node 3 pre:  (struct Node *) 0x6040b0
10. Node 3 next:(struct Node *) 0x604070
*/

#include <malloc.h>
#include <stdio.h>
#include "mylib.h"
#include "list.h"

/*=========================================================================
 struct Node Node

    Description:  Node inside the list to hold the inputting elements and 
                  positions  
    Data Fields:
        pre (Node *)  - how to access the prior Node
        next (Node *)  - how to accsee the next Node
        data (void *) - the data to store

    Public functions:
                    None
==========================================================================*/
typedef struct Node {
        struct Node * pre;      /* how to access the prior Node */
        struct Node * next;     /* how to access the next Node */
        void * data;            /* the data to store */
} Node;

/*=========================================================================
 struct Node List

    Description:  List holds all the nodes and accessing them through the 
                  end pointer.
    Data Fields:
        end (Node *)  - end of the list
        list_count (long)  - which list is it
        occupancy (long)  - how many items in the list
        

    Public functions:
        copy_func (void* (*)(void*)) - copy function
        delete_func (void(*) (void *)) - delete function
        write_func (FILE *(*) (void*,FILE *)) - write fucntion
==========================================================================*/
typedef struct List {
        Node * end;             /* the end of the list */
        long list_count;        /* which list is it */
        long occupancy;
        void *(*copy_func) (void *);
        void (*delete_func) (void *);
        FILE *(*write_func) (void *, FILE *);
} List;

/* private Node function declarations */
static long check_to_go_forward (List * this_list, long where);
static void delete_Node (Node **, void (*delete_func) (void *));
static Node * find_location (List * this_list, long where);
static Node * insert_Node (Node *, void *, void *(*copy_func) (void *)); 
static Node * new_Node (void *, void *(*copy_func) (void *));
static void * remove_Node (Node *);
static void * view_Node (Node *); 
static FILE * write_Node (Node *, FILE *, FILE *(*write_func) (void *, FILE *));

/* catastrophic error messages */
static const char ADNEXT_NONEXIST[] = 
                "Advance next from non-existent list!!!\n";
static const char ADNEXT_EMPTY[] = 
                "Advance next from empty list!!!\n";
static const char ADPRE_NONEXIST[] = 
                "Advance pre from non-existent list!!!\n";
static const char ADPRE_EMPTY[] = 
                "Advance pre from empty list!!!\n";
static const char CHECK_NONEXIST[] =
                "Checking direction on non-existent list!!!\n";
static const char DELETE_NONEXIST[] =
                "Deleting from non-existent list!!!\n";
static const char DELETE_NONEXISTNODE[] =
                "Deleting a non-existent node!!!\n";
static const char ISEMPTY_NONEXIST[] =
                "Is empty check from non-existent list!!!\n";
static const char INSERT_NONEXIST[] =
                "Inserting to a non-existent list!!!\n";
static const char REMOVE_NONEXIST[] =
                "Removing from non-existent list!!!\n";
static const char REMOVE_EMPTY[] =
                "Remove from empty list!!!\n";
static const char VIEW_NONEXIST[] = 
                "Viewing a non-existent list!!!\n";
static const char VIEW_NONEXISTNODE[] = 
                "Viewing a non-existent node!!!\n";
static const char VIEW_EMPTY[] =
                "Viewing an empty list!!!\n";
static const char WRITE_NONEXISTFILE[] =
                "Writing to a non-existent file!!!\n";
static const char WRITE_NONEXISTLIST[] =
                "Writing from a non-existent list!!!\n";
static const char WRITE_MISSINGFUNC[] =
                "Don't know how to write out elements!!!\n";
static const char WRITE_NONEXISTNODE[] =
                "Writing from a non-existent node!!!\n";

/* debug messages */
static const char ADNEXT[] = "[List %ld - Advancing next]\n";
static const char ADPRE[] = "[List %ld - Advancing pre]\n";
static const char INSERT[] = "[List %ld - Inserting node]\n";
static const char REMOVE[] = "[List %ld - Removing node]\n";
static const char VIEW[] = "[List %ld - Viewing node]\n";
static const char LIST_ALLOCATE[] = "[List %ld has been allocated]\n";
static const char LIST_DEALLOCATE[] = "[List %ld has been deallocated]\n";

static int debug_on = FALSE;    /* allocation of debug flag */
static long list_counter = 0;   /* the number of lists allocated so far */
/*---------------------------------------------------------------------------
Function Name:                set_debug_off
Purpose:                      check if the debug message is turned on or off
Description:                  this function set the debug_on to FALSE
Input:                        void
Output:                       None.
Result:                       debug_on = FALSE;
---------------------------------------------------------------------------*/
void set_debug_off (void) {
	/* set debug_on to FALSE */
	debug_on = FALSE;
}
/*---------------------------------------------------------------------------
Function Name:                set_debug_on
Purpose:                      check if the debug message is turned on or off
Description:                  this function set the debug_on to TRUE
Input:                        void
Output:                       None.
Result:                       debug_on = TRUE;
---------------------------------------------------------------------------*/
void set_debug_on (void) {
	/* set debug_on to TRUE */
	debug_on = TRUE;
}
/*---------------------------------------------------------------------------
Function Name:                advance_next_List
Purpose:                      move to the next item in the list
Description:                  this function moves to the next item in the 
                              list by changing the end pointer of the list.
Input:                        this_list (List *) - current list we have
Output:                       debug message
                              is list do not exist, output error message 
Result:                       void function
                              end pointer moves next
---------------------------------------------------------------------------*/
void advance_next_List (List * this_list) {
        /* debug message */
        if (debug_on){
            fprintf(stderr, ADNEXT, this_list->list_count);
        }
        /* check if we are advance next a nonexisting list */
        if (!this_list){
            fprintf(stderr,ADNEXT_NONEXIST);
        }
        /* check if the list is empty */
        if (isempty_List(this_list)){
            fprintf(stderr,ADNEXT_EMPTY);
        }
	else
		/* change the end pointer to the next pointer 
		to get value of next node */
		this_list->end = this_list->end->next;
}
/*---------------------------------------------------------------------------
Function Name:                advance_pre_List
Purpose:                      move to the pre item in the list
Description:                  this function moves to the pre item in the 
                              list by changing the end pointer of the list.
Input:                        this_list (List *) - current list we have
Output:                       debug message
                              is list do not exist, output error message 
Result:                       void function
                              end pointer moves pre
---------------------------------------------------------------------------*/
void advance_pre_List (List * this_list) {
        /* debug message */
        if (debug_on){
            fprintf(stderr, ADPRE, this_list->list_count);
        }
        /* check if we are advance pre a nonexisting list */
        if (!this_list){
            fprintf(stderr,ADPRE_NONEXIST);
        }
        /* check if the list is empty */
        if (isempty_List(this_list)){
            fprintf(stderr,ADPRE_EMPTY);
        }
	else
		/* change the end pointer to the pre pointer 
		to get value of pre node */
		this_list->end = this_list->end->pre;
}

/*---------------------------------------------------------------------------
Function Name:                check_to_go_forward
Purpose:                      checks to go froward or not
Description:                  This function checks whether it would be more 
                              efficient to reach item number where in the list
                              by looping forwards from the end of the list 
                              (true is returned) or backwards from the end of 
                              the list (false is returned).
Input:                        this_list (List *) - current list we have
                              where (long) - the point we are moving to
Output:                       is list do not exist, output error message 
Result:                       return true of false
---------------------------------------------------------------------------*/
static long check_to_go_forward (List * this_list, long where) {
        /* check if we are checking a nonexisting list */
        if (!this_list){
            fprintf(stderr, CHECK_NONEXIST);
        }
        /* if where is bigger than occupancy minus where, go forward
        return true, if not, go backword, return false */ 
        if (where <= this_list->occupancy-where+1){
            return TRUE;
        }
        else 
            return FALSE;
}
/*---------------------------------------------------------------------------
Function Name:                delete_List
Purpose:                      delete each items in the list and the free the 
                              list
Description:                  This destructor function deallocates all memory 
                              associated with the list, including the memory 
                              associated with all of the nodes in the list. 
                              It sets the list pointer in the calling function
                              to NULL.
Input:                        lpp (List **) -  a double pointer to the list 
                              that is to be deleted
Output:                       debug message
                              if the list do not exist, output error message
Result:                       void funcion
---------------------------------------------------------------------------*/
void delete_List (List ** lpp) {
        /* to know how many node to delete */
	long count;
        /* working node */
	Node * working = (*lpp)->end;
	/* check if the list exist */
        if (!lpp || !*lpp){
                fprintf(stderr, DELETE_NONEXIST);
                return;
        }
	if (!working){
		return;
	}
	    /* debug message */
        if (debug_on){
                fprintf(stderr,LIST_DEALLOCATE,list_counter);
        }
        /* call delete_Node to delete all the Node in the list*/
        for (count = 1; count < (*lpp)->occupancy; count++) {
                 /*move the end pointer forward */
                (*lpp)->end = (*lpp)->end->next;
                delete_Node (&working, (*lpp)->delete_func);
		        working = (*lpp)->end;
        }
	if ((*lpp)->occupancy != 0){
		delete_Node(&working,(*lpp)->delete_func);
	}
	/* delete list */
	free(*lpp);
	/* assign list to NULL */
	*lpp = NULL;
	/* decrease list counter */
	list_counter--;
}

/*---------------------------------------------------------------------------
Function Name:                find_location
Purpose:                      find the location of the node
Description:                  This function is used to eliminate code 
                              duplication in the list functions by finding 
                              the location at which we wish to insert, 
                              remove, or view. find_location should be used 
                              to locate the Node at location where.
Input:                        this_list (List *) - current list we have
                              where (long) - the point we are moving to
Output:                       if list do not exist, output error message 
Result:                       return the located node
---------------------------------------------------------------------------*/
static Node * find_location (List * this_list, long where) {
        /* create a counter in order to count how many advance should
        we make, initialize it to be occupancy */
        long counter = this_list->occupancy;
        /* create a Node to hold the end pointer in order to return */
        Node * location_Node;
        /* check if the list is empty */
        if (isempty_List(this_list)){
            location_Node = NULL;
        }
        /* when where is less than or equal to 1, or where is bigger than
        occupancy, let location_Node be the current end pointer 
        in this case, we are finding nodes when where == 0 or 1 or other 
        positions not exist yet */
        if (where <= 1 || where > this_list->occupancy){
            location_Node = this_list->end;
        }
        /* in this case, we are finding nodes when where is bigger than 1 
        and less than or equal to occupancy */
        else{
            /* check for moving end pointer forward or backward 
            if true, forward using advance_next_list */
            if(check_to_go_forward(this_list,where)){
                /* if we go forward, set counter to 0 */
                counter = 0;
                /* using while loop to advance end pointer to the next */
                while (counter != where-1){
                    advance_next_List(this_list);
                    counter++;
                }          
            }
            /* if checking is false, move backward,using advance_pre_list */
            else{
                /* using while loop to advance end pointer to the pre */
                while (counter != where-1){
                    advance_pre_List(this_list);
                    counter--;
                }
            }
            /* set end pointer to location_Node */
            location_Node = this_list->end;
        }
        return location_Node;
}
/*---------------------------------------------------------------------------
Function Name:                insert
Purpose:                      insert an item to the list
Description:                  Inserts the element into this_list at location 
                              where. find_location should be used to locate 
                              the Node at location where.
Input:                        this_list (List *) - current list we have
                              where (long) - the point we are moving to
                              element (void *) - a pointer to the object we 
                              wish to insert in the list
Output:                       if list do not exist, output error message 
                              debug message
Result:                       return true or false
---------------------------------------------------------------------------*/
long insert (List * this_list, void * element, long where) {
        /* create a node to save the current end pointer */
        Node * prior_end = this_list->end;
        /* create a node to hold the node at where */
        Node * pre_Node = find_location(this_list,where);
        /* let end pointer pointing be the new node we are inserting */
        this_list->end = insert_Node(pre_Node,element,this_list->copy_func);
        /* set the prior value to end pointer 
        this case is for where == 1 and where smaller 
        than or equal to occupancy */
        /* check if ths list is empty */
        if (!this_list){
            fprintf(stderr, INSERT_NONEXIST);
            return FALSE;
        }
        /* debug message */
        if (debug_on){
            fprintf(stderr, INSERT,this_list->list_count);
	    }
	    /* set end pointer to prior end pointer after we insert
	    * inside or before the list but not at the end */
        if(1 <= where && where <= this_list->occupancy){
            this_list->end = prior_end;
        }
        /* increase occupancy */
        this_list->occupancy++;
        return TRUE;
}
 /*---------------------------------------------------------------------------
Function Name:                isempty_List
Purpose:                      check if the list is empty
Description:                  Checks to see if this_list is empty.
Input:                        this_list (List *) - current list we have
Output:                       if list do not exist, output error message 
Result:                       void function
---------------------------------------------------------------------------*/
long isempty_List (List * this_list) {
        /* check if the list is not exist */
        if (!this_list){
                fprintf(stderr,ISEMPTY_NONEXIST);
        }
        /* check the occupancy if 0, if it is, the list is empty
        return true, if not, list is not empty, return false */
        if (this_list->occupancy ==0){
            return TRUE;
        }
        else 
            return FALSE;
}
/*---------------------------------------------------------------------------
Function Name:                new_List
Purpose:                      create a new list
Description:                  This constructor function allocates and 
                              initializes a new List object. It initializes 
                              the list data fields, and returns a pointer to 
                              the list. All new lists should be empty.
Input:                        nothing
Output:                       debug message
Result:                       return list be created
---------------------------------------------------------------------------*/
List * new_List (
        void *(*copy_func) (void *),
        void (*delete_func) (void *),
        FILE *(*write_func) (void *, FILE *)) {
        /* create a new list pointer with sizeof List(type) */
	    List * this_list = (List *) malloc (sizeof(List));
        /* set the end pointer to NULL */
        this_list->end = NULL;
        /* increase the list_count with one each time we create a new list */
        this_list->list_count = ++list_counter;
        /* set occupancy to be 0, repersenting how many Nodes in the list */
        this_list->occupancy = 0;
        /* set funciton pointers be the function we passed in as parameter */
        this_list->copy_func = copy_func;
        this_list->delete_func = delete_func;
        this_list->write_func = write_func;
        /* debug message */
        if (debug_on){
                fprintf(stderr,LIST_ALLOCATE,this_list->list_count);
        }
        return this_list;
}
/*---------------------------------------------------------------------------
Function Name:                remove_List
Purpose:                      remove one item from the list
Description:                  Removes an element in this_list at location 
                              where. find_location should be used to locate 
                              the Node at location where.
Input:                        this_list (List *) - current list we have
                              where (long) - the point we are moving to
Output:                       debug message
                              if the list is empty, error message
                              if the list do not exist, output error message
Result:                       return the date of the element be removed
---------------------------------------------------------------------------*/
void * remove_List (List * this_list, long where) {
	    /* create a Node to hold the Node to remove */
        Node * Node_to_remove = NULL;
	    /* create a pointer to hold the data of the removing Node */
        void * removeNode_data;
	    /* create a Node to hold the new or prior end pointer */
        Node * new_end = this_list->end;
	    /* find the remove node */
        Node_to_remove = find_location(this_list,where);
	    /* check if the list exist */
        if (!this_list){
            fprintf(stderr, REMOVE_NONEXIST);
            return NULL;
        }
	    /* check if the list is empty */
        if (isempty_List(this_list)){
            fprintf(stderr, REMOVE_EMPTY);
            return NULL;
        }
	    /* check if we are removing at the end of the list, 
	    * if we are not, move the Node forward */
        if(where != 0 && where < this_list->occupancy){
            Node_to_remove = this_list->end->next;
        }
        /* special case when where equals occupancy */
        else if (where == this_list->occupancy){
            new_end = this_list->end;
            Node_to_remove = this_list->end->next;
        }
        /* all other situations */
        else {
            new_end = this_list->end->pre;
        }
        /* call remove_Node to remove */
        removeNode_data = remove_Node(Node_to_remove);
	    /* set the end pointer to prior end */
        this_list->end = new_end;
	    /* decrease the occupancy */
        this_list->occupancy--;
        /* if the list is empty after remove, set end to null */
        if (isempty_List(this_list)){
            this_list->end = NULL;
        }
         /* set the holding node to NULL;*/
        Node_to_remove = NULL;
	    /* debug message */
        if (debug_on){
            fprintf(stderr,REMOVE,this_list->list_count);
        }
        return removeNode_data;
}
/*---------------------------------------------------------------------------
Function Name:                view_List
Purpose:                      view one item from the list
Description:                  Returns a pointer to the object stored at 
                              location where for viewing. find_location 
                              should be used to locate the Node at location 
                              where. 
Input:                        this_list (List *) - current list we have
                              where (long) - the point we are moving to
Output:                       debug message
                              if the list is empty, error message
                              if the list do not exist, output error message
Result:                       return the date of the element be viewed
---------------------------------------------------------------------------*/
void * view (List * this_list, long where) {
	/* create a Node to store the Node we are viewing */
        Node * Node_to_view;
	/* create a Node to hold the prior end pointer */
        Node * prior_end = this_list->end;
	/* create a pointer to store the data of the Node we are
	 * viewing */
        void * data_view;
	/* call find_location to find the Node */
        Node_to_view = find_location(this_list,where);
        /* check if list is NULL */
        if (!this_list){
            fprintf(stderr, VIEW_NONEXIST);
            return NULL;
        }
	/* check if the list is empty */
        if (isempty_List(this_list)){
            fprintf(stderr, VIEW_EMPTY);
            return NULL;
        }
	/* debug message */
        if (debug_on){
            fprintf(stderr,VIEW,this_list->list_count);
        }
	/* when we are not viewing the end of the list, move forward*/
        if(where != 0 && where <= this_list->occupancy){
            Node_to_view = this_list->end->next;
        }
	/* set the end pointer to prior end */
        this_list->end = prior_end;
	/* get the data of viewing Node */
        data_view = view_Node(Node_to_view);
        return data_view;
}
/*---------------------------------------------------------------------------
Function Name:                write_List
Purpose:                      print out the date of the elements in the list
Description:                  Writes the elements of this_list forwards, 
                              starting with the last item. The list is printed 
                              to filestream stream.
Input:                        this_list (List *) - current list we have
                              stream (FILE *) - are expected to be either 
                              stdout or stderr
Output:                       if the list do not exist, output error message
                              if the stream do not exist, output error message
Result:                       output each item value in the list, return stream
---------------------------------------------------------------------------*/
FILE * write_List (List * this_list, FILE * stream) {
        /* to know how many elements to print */
        long count;             
        /* working node */
        Node * working;                 
        /* check if file exist */
        if (!stream) {
                fprintf (stderr, WRITE_NONEXISTFILE);
                return NULL;
        }
        /* check if this_list exist */
        if (!this_list) {
                fprintf (stderr, WRITE_NONEXISTLIST);
                return NULL;
        }
        /* print out list number and how many Nodes in list */
        if (stream == stderr)
                fprintf (stream, "List %ld has %ld items in it.\n",
                        this_list->list_count, this_list->occupancy);
        /* check if write funcion exist */  
        if (!this_list->write_func) {
                fprintf (stream, WRITE_MISSINGFUNC);
                return stream;
        }
        /* when there are more than 1 value in this_list
        set working to end pointer to next */
        if (this_list->occupancy >= 1)
                working = this_list->end->next;
        /* using a loop to print out each element in the list */
        for (count = 1; count <= this_list->occupancy; count++) {
                if (stream == stderr)
                        fprintf (stream, "\nelement %ld:  ", count);
                write_Node (working, stream, this_list->write_func);
                /* ->next make working goes forward */
                working = working->next;
        }
                
        return stream;
}
/*---------------------------------------------------------------------------
Function Name:                write_reverse_List
Purpose:                      print out the date of the elements in the list
Description:                  Writes the elements of this_list backwards, 
                              starting with the last item. The list is printed 
                              to filestream stream.
Input:                        this_list (List *) - current list we have
                              stream (FILE *) - are expected to be either 
                              stdout or stderr
Output:                       if the list do not exist, output error message
                              if the stream do not exist, output error message
Result:                       output each item value in the list, return stream
---------------------------------------------------------------------------*/
FILE * write_reverse_List (List * this_list, FILE * stream) {
        /* to know how many elements to print */
        long count;             
        /* working node */
        Node * working;                 
        /* check if file exist */
        if (!stream) {
                fprintf (stderr, WRITE_NONEXISTFILE);
                return NULL;
        }
        /* check if this_list exist */
        if (!this_list) {
                fprintf (stderr, WRITE_NONEXISTLIST);
                return NULL;
        }
        /* print out list number and how many Nodes in list */
        if (stream == stderr)
                fprintf (stream, "List %ld has %ld items in it.\n",
                        this_list->list_count, this_list->occupancy);
        /* check if write funcion exist */    
        if (!this_list->write_func) {
                fprintf (stream, WRITE_MISSINGFUNC);
                return stream;
        }
        /* when there are more than 1 value in this_list
        set working to end pointer */
        if (this_list->occupancy >= 1)
                working = this_list->end;
        /* using a loop to print out each element in the list */
        for (count = 1; count <= this_list->occupancy; count++) {
                if (stream == stderr)
                        fprintf (stream, "\nelement %ld:  ", count);
                write_Node (working, stream, this_list->write_func);
                /* ->pre make working goes backward */
                working = working->pre;
        }
        return stream;
}
/*---------------------------------------------------------------------------
Function Name:                delete_Node
Purpose:                      delete one Node
Description:                  This destructor function deallocates all memory 
                              associated with the Node
Input:                        npp (Node **) -  a double pointer to the Node 
                              that is to be deleted
                              delete_func (void(*)(void *)) - delete_funciton
Output:                       if the Node do not exist, output error message
Result:                       void funcion
---------------------------------------------------------------------------*/
static void delete_Node (Node ** npp, void (*delete_func) (void *)) {

        /* does the node exist??? */
        if (!npp || !*npp) {
                fprintf (stderr, DELETE_NONEXISTNODE);
                return;
        }

        /* call function to delete element */
        if (delete_func && (*npp)->data)
                (*delete_func) (&((*npp)->data));

        /* delete element */
        free (*npp);

        /* assign node to NULL */
        *npp = NULL;
}
/*---------------------------------------------------------------------------
Function Name:                insert_Node
Purpose:                      insert a Node
Description:                  Creates a new node to hold element, or, if 
                              copy_func is non-NULL, a copy of element. 
                              This new node is then incorporated into the 
                              list at the location AFTER this_Node. 
                              Returns a pointer to the new node that has 
                              been inserted into the list.t
Input:                        this_Node (Node *) - current Node we have
                              element (void *) - a pointer to the object we 
                              wish to insert in the Node
                              copy_func (void *(*)(void*)) - copy function
Result:                       return the node we inserted
---------------------------------------------------------------------------*/
static Node * insert_Node (Node * this_Node, void * element, 
        void * (*copy_func) (void *)) {
        /* creates a new node to hold element */
        Node * working;
        /* calling new_Node method to initialize it */
        working = new_Node(element,copy_func);
        /* check for first Node */
        if (this_Node == NULL){
            /* if we are inserting the first node, 
            let pre and next of working be itself */
            working->pre = working;
            working->next = working;
        }
        else {
            /* attach the new Node to this_list */
            working->pre = this_Node;
            working->next = this_Node->next;
            /* integrate teh new Node into the list */
            this_Node->next = working;
            working->next->pre = working;
        }
        return working;
}

/*---------------------------------------------------------------------------
Function Name:                new_Node
Purpose:                      create a new Node
Description:                  Creates a new node to hold element
Input:                        element (void *) - a pointer to the object we 
                              wish to insert in the Node
                              copy_func (void *(*)(void*)) - copy function
Result:                       return the node we created
---------------------------------------------------------------------------*/
static Node* new_Node (void * element, void * (*copy_func) (void *)) {

        /* allocate memory */
        Node *this_Node = (Node *) malloc (sizeof (Node));

        /* initialize memory */
        /* set next and pre of this_Node to NULL */
        this_Node->next = this_Node->pre = NULL;
        /* check if we have copy function, if we have, make a copy of 
        the element, if we don't, give element to data of this_Node */
        this_Node->data = (copy_func) ? (*copy_func) (element) : element;

        return this_Node;
}
/*---------------------------------------------------------------------------
Function Name:                remove_Node
Purpose:                      remove a Node
Description:                  "Unlinks" this_Node from the list by arranging 
                              the pointers of the surrounding Nodes so they 
                              no longer point to this_Node. The memory 
                               with the Node object is freed, 
                              but the Node's data is not deleted. 
                              A pointer to the data is returned.
Input:                        this_Node (Node *) - current Node we have
Result:                       the data of the removed node
---------------------------------------------------------------------------*/
static void * remove_Node (Node * this_Node) {
	/* create a void pointer to hold the data of removing Node */
        void * data_remove = this_Node->data;
	/* change the Nodes around current Node */
        this_Node->pre->next = this_Node->next;
        this_Node->next->pre = this_Node->pre;
	/* delete the node but not deleting the data */
        delete_Node(&this_Node, 0);
        return data_remove;
}
/*---------------------------------------------------------------------------
Function Name:                view_Node
Purpose:                      view a Node
Description:                  Returns a pointer to this_Node's, data.
Input:                        this_Node (Node *) - current Node we have
Output:                       if the Node do not exist, output error meeage
Result:                       the data of the viewed node
---------------------------------------------------------------------------*/
static void * view_Node (Node * this_Node) {
        /* check if the node is NULL */
        if (!this_Node){
            fprintf(stderr, VIEW_NONEXISTNODE);
            return NULL;
        }
        /* returns a pointer to this_Node's data */
        return this_Node->data;
}
/*---------------------------------------------------------------------------
Function Name:                write_Node
Purpose:                      print out the value of the node
Input:                        this_Node (Node *) - current Node we have
                              stream (FILE *) - stderr or stdout
                              writ_func (FILE*(*)(void*,FILE*)) - write function
Output:                       if the Node do not exist, output error meeage
                              if stream do not exist, out put error message
                              if write function do not exist, out put error 
                              message
---------------------------------------------------------------------------*/
static FILE* write_Node (Node * this_Node, FILE * stream,
        FILE * (*write_func) (void *, FILE *)) {
        /* check if stream exist */
        if (!stream) {
                fprintf (stderr, WRITE_NONEXISTFILE);
                return NULL;
        }
        /* check if node exist */
        if (!this_Node) {
                fprintf (stream, WRITE_NONEXISTNODE);
                return stream;
        }
        /* check if write function exist */
        if (!write_func) {
                fprintf (stream, WRITE_MISSINGFUNC);
                return stream;
        }

        return (*write_func) (this_Node->data, stream);
}
