#include "tree.h"
#include "treeDump.h"
#include "akinator.h"
#include "treeFileFunc.h"

int main ()
{
    Node *root = NULL;
    nodeCtor (&root, "Животное?");

    branchCtor (root, LEFT_NO, "Полотенце");
    branchCtor (root, RIGHT_YES, "Кошка");

    //makeTreeFromFile ("logfile.txt", root);

    akinator (root);

    treePrint (root);

    treeDump (root);

    treeDtor (root);
}