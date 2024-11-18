#ifndef AKINATOR_H_
#define AKINATOR_H_

#include "tree.h"

const size_t MAX_WAY_SIZE = 10;

bool guessElement (Node *node);
bool findLeafElement (Node **currentNode);
bool getElement (char *element);
bool giveDefinition (char *data, Node *root);
bool findDifferences (char *dataFirst, char *dataSecond, Node *root);

#endif