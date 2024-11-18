#include "tree.h"
#include "treeDump.h"
#include "akinator.h"
#include "treeFileFunc.h"

int main ()
{
    Node *root = NULL;
    nodeCtor (&root, POISON, NULL);

    //branchCtor (root, LEFT_NO, "Полотенце");
    //branchCtor (root, RIGHT_YES, "Кошка");

    makeTreeFromFile ("logfile.txt", root);

    //guessElement (root);

    //treePrint (root);

    treeDump (root, WIDE);

    giveDefinition ("Полторашка", root);

    treeDump (root, WIDE);

    treeDtor (root);
}