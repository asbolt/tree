#ifndef TREE_DUMP_H
#define TREE_DUMP_H

#include "tree.h"

FUNCTION_STATUS treeDump (Node *root);
FUNCTION_STATUS treeDumpMakeNodeLabels (Node *root, int rang, FILE *dotFile);
FUNCTION_STATUS treeDumpMakeArrows (Node *root, FILE *dotFile);

#endif