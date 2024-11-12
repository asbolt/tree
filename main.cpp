#include "tree.h"
#include "treeDump.h"

int main ()
{
    Node *root = NULL;
    nodeCtor (&root, 15);

    treeAddElement (root, 10);
    treeAddElement (root, 20);
    treeAddElement (root, 12);
    treeAddElement (root, 9);

    treePrint (root);

    treeDump (root);

    treeDtor (root);
}