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

struct Node 
{
    char *data            = NULL;
    Node *left            = NULL;
    Node *right           = NULL;
};

enum BRANCH
{
    LEFT_NO               = 1,
    RIGHT_YES             = 2
};

bool nodeCtor (Node **node, char * value);
bool treeAddElement (Node *node, char * value);
bool treeDtor (Node *node);
bool treePrint (Node *node);
bool print (Node *node, FILE *logFile);
bool branchCtor (Node *node, int branch, char * value);

#endif

