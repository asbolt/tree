#ifndef TREE_FILE_FUNC_H
#define TREE_FILE_FUNC_H

#include "tree.h"

bool makeTreeFromFile (const char *file, Node *root);
bool makeTreeNodesFromFile (char *node, char *buffer, Node *root, FILE *treeFile);

#endif