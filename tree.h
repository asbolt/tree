#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include <cstring>

#define LOG_FILE "logfile.txt"

const char POISON[] = "а";
const int MAX_ANSWER_SIZE = 8;
const size_t MAX_LEAF_SIZE = 150;

enum TREE_ERRORS
{
    TREE_NULL      = 1,
    TREE_DATA_NULL = 2,
    TREE_GOOD      = 0
};

struct Node 
{
    Node *parent = NULL;
    char *data   = NULL;
    Node *left   = NULL;
    Node *right  = NULL;
};

enum BRANCH
{
    LEFT_NO   = 1,
    RIGHT_YES = 2
};

bool nodeCtor (Node **node, const char * value, Node *parent);
bool treeAddElement (Node *node, char * value);
bool treeDtor (Node *node);
bool treePrint (Node *node);
bool print (Node *node, FILE *logFile);
bool branchCtor (Node *node, int branch, const char * value);
Node *findElement (char *data, Node *root, Node *node, int *way, int ind);
TREE_ERRORS checkForErrors (Node *root);

#endif

