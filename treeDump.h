#ifndef TREE_DUMP_H
#define TREE_DUMP_H

#include "tree.h"

enum MODE
{
    WIDE,
    NARROW
};

bool treeDump (Node *root, int mode);
bool treeDumpMakeNodeLabels (Node *root, int rang, FILE *dotFile, int mode);
bool treeDumpMakeArrows (Node *root, FILE *dotFile);

#endif