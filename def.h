#ifndef _DEF_
#define _DEF_

// new types
typedef void* DATA;

// Node
typedef struct node
{
    DATA key;
    struct node* next;
}NODE;

typedef enum { False, True } BOOL;	// a boolean type


#endif