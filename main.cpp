#include "tree.h"
#include "treeDump.h"
#include "akinator.h"
#include "treeFileFunc.h"

int main ()
{
    Node *root = NULL;
    char a[6] = "a";
    nodeCtor (&root, a);

    //branchCtor (root, LEFT_NO, "Ященко");
    //branchCtor (root, RIGHT_YES, "Сугакевич");

    makeTreeFromFile ("logfile.txt", root);

    akinator (root); 
    //akinator (root);

    treePrint (root);

    treeDump (root);

    treeDtor (root);
}