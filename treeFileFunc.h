#ifndef TREE_FILE_FUNC_H
#define TREE_FILE_FUNC_H

#include "tree.h"

FUNCTION_STATUS makeTreeFromFile (const char *file, Node *root);
FUNCTION_STATUS makeTreeNodesFromFile (char *node, char *buffer, Node *root, FILE *treeFile);

#endif