#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <cstring>

#define LOG_FILE "logfile.txt"
#define POISON (char*)POISON_

const char POISON_[5] = "а";
const int MAX_ANSWER_SIZE = 8;
const size_t MAX_LEAF_SIZE     = 150;
const size_t MAX_QUESTION_SIZE = 150;

struct Node 
{
    char *data            = NULL;
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
    LEFT_NO               = 1,
    RIGHT_YES             = 2
};

FUNCTION_STATUS nodeCtor (Node **node, char * value);
FUNCTION_STATUS treeAddElement (Node *node, char * value);
FUNCTION_STATUS treeDtor (Node *node);
FUNCTION_STATUS treePrint (Node *node);
FUNCTION_STATUS print (Node *node, FILE *logFile);
FUNCTION_STATUS branchCtor (Node *node, int branch, char * value);

#endif

