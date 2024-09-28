/**************/
/*   list.c   */
/**************/


#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//////////////////////////////////////////
// Init
// Aim:		create new list
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
//////////////////////////////////////////
BOOL L_init(LIST* pList)
{
    if (pList == NULL)
        return False;	// no list to initialize

    pList->head = *(NODE*)malloc(sizeof(NODE));
    if (&pList->head == NULL) {
        return False; // Allocation failed
    }

    pList->head.next = NULL;
    return True;
}


/////////////////////////////////////////////////////////////////
// Insert
// Aim:		add new node
// Input:	pointer to the node BEFORE the place for the new one
//			a value to be stored in the new node
// Output:	pointer to the new node
/////////////////////////////////////////////////////////////////
NODE* L_insert(NODE* pNode, DATA Value)
{
    NODE* tmp;

    if (!pNode)
        return NULL;

    tmp = (NODE*)malloc(sizeof(NODE));

    if (tmp != NULL) {
        tmp->key = Value;
        tmp->next = pNode->next;
        pNode->next = tmp;
    }
    return tmp;
}


//////////////////////////////////////////////////////////////
// Delete
// Aim:		erase node
// Input:	pointer to the node BEFORE the node to be deleted
// Output:	TRUE if succeeded
//////////////////////////////////////////////////////////////
BOOL L_delete(NODE* pNode, void (*freeFunc)(void*))
{
    NODE* tmp;
    if (!pNode)
        return False;
    tmp = pNode->next;
    if (!tmp)
        return False;

    pNode->next = tmp->next;
    free(tmp);
    return True;
}

/////////////////////////////////////////////////////////
// Find
// Aim:		search for a value
// Input:	pointer to the node to start with
//			a value to be found
// Output:	pointer to the node containing the Value
/////////////////////////////////////////////////////////
const NODE* L_find(const NODE* pNode, DATA Value)
{
    const NODE* tmp = pNode;

    while (tmp != NULL)
    {
        if (tmp->key == Value)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}

////////////////////////////////////////////////
// Free (additional function)
// Aim:		free the list memory
// Input:	pointer to the list structure
// Output:	TRUE if succeeded
////////////////////////////////////////////////
BOOL L_free(LIST* pList, void (*freeFunc)(void*))
{
    NODE* tmp;

    if (!pList) return False;
    tmp = &(pList->head);
    BOOL res = True;
    while (res)
    {
        res = L_delete(tmp, freeFunc);
    }

    return True;
}



////////////////////////////////////////////////
// Print (additional function)
// Aim:		print the list content (assume the DATA is int)
// Input:	pointer to the list structure
// Output:	a number of the printed elements
////////////////////////////////////////////////
void L_print(const LIST* pList, void (*printFunc)(void*))
{
    NODE* tmp;

    if (!pList) {
        printf("List is empty\n");
        return;
    }
    printf("\n");
    tmp = pList->head.next;
    while (tmp != NULL)
    {
        printFunc(tmp->key);
        tmp = tmp->next;
    }
    printf("\n");
}
