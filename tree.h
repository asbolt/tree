#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

#define LOG_FILE "logfile.txt"

typedef int tree_element;

const tree_element POISON = -154;

struct Node 
{
    int data              = POISON;
    Node *left            = NULL;
    Node *right           = NULL;
};

enum FUNCTION_STATUS
{
    CORRECT               = 0,
    ERROR                 = 1
};

enum BRANCH
{
    LEFT                  = 1,
    RIGHT                 = 2
};

FUNCTION_STATUS nodeCtor (Node **node, int value);
FUNCTION_STATUS treeAddElement (Node *node, tree_element value);
FUNCTION_STATUS treeDtor (Node *node);
FUNCTION_STATUS treePrint (Node *node);
FUNCTION_STATUS print (Node *node, FILE *logFile);
FUNCTION_STATUS branchCtor (Node *node, int branch, int value);

#endif

