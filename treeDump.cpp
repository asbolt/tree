#include "treeDump.h"

FUNCTION_STATUS treeDump (Node *root)
{
    FILE * dotFile = fopen ("dot.dot", "wb");
        if (dotFile == NULL)
        {
            return ERROR;
        }

    fprintf (dotFile, "digraph G{\nrankdir=HR;\n");

    int rang = 0;
    treeDumpMakeNodeLabels (root, rang, dotFile);

    treeDumpMakeArrows (root, dotFile);

    fprintf (dotFile, "}");

    fclose (dotFile);

    system ("dot dot.dot -Tpng -o gr.png");

    return CORRECT;
}

FUNCTION_STATUS treeDumpMakeNodeLabels (Node *root, int rang, FILE *dotFile)
{
    fprintf (dotFile, "node%p [shape=\"rectangle\", label = \"%s\", rang = %d]\n", root, root->data, rang);

    if (root->left != NULL)
    {
        treeDumpMakeNodeLabels (root->left, rang + 1, dotFile);
    }

    if (root->right != NULL)
    {
        treeDumpMakeNodeLabels (root->right, rang + 1, dotFile);
    }

    return CORRECT;
}

FUNCTION_STATUS treeDumpMakeArrows (Node *root, FILE *dotFile)
{
    if (root->left != NULL)
    {
        fprintf (dotFile, "node%p -> node%p [label = \"нет\"]\n", root, root->left);
    }
    
    if (root->right != NULL)
    {
        fprintf (dotFile, "node%p -> node%p [label = \"да\"]\n", root, root->right);
    }

    if (root->left != NULL)
    {
        treeDumpMakeArrows (root->left, dotFile);
    }

    if (root->right != NULL)
    {
        treeDumpMakeArrows (root->right, dotFile);
    }

    return CORRECT;
}