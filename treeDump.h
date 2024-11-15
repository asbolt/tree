#ifndef TREE_DUMP_H
#define TREE_DUMP_H

#include "tree.h"

bool treeDump (Node *root);
bool treeDumpMakeNodeLabels (Node *root, int rang, FILE *dotFile);
bool treeDumpMakeArrows (Node *root, FILE *dotFile);

#endif