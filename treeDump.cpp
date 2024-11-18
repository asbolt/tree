#include "treeDump.h"

bool treeDump (Node *root, int mode)
{
    FILE * dotFile = fopen ("dot.dot", "wb");
        if (dotFile == NULL)
        {
            return false;
        }

    fprintf (dotFile, "digraph G{\nrankdir=HR;\n");

    int rang = 0;

    treeDumpMakeNodeLabels (root, rang, dotFile, mode);

    treeDumpMakeArrows (root, dotFile);

    fprintf (dotFile, "}");

    fclose (dotFile);

    system ("dot dot.dot -Tpng -o gr.png");

    return true;
}

bool treeDumpMakeNodeLabels (Node *root, int rang, FILE *dotFile, int mode)
{
    if (mode == NARROW)
    {
        fprintf (dotFile, "node%p [shape=\"rectangle\", label = \"%s\", rang = %d]\n", root, root->data, rang);
    } else if (mode == WIDE)
    {
        fprintf (dotFile, "node%p [shape=record, label = \"{%p | {%s} | {%p | %p}}\", rang = %d]\n", root, root->parent, root->data, root->left, root->right, rang);
    }

    if (root->left != NULL)
    {
        treeDumpMakeNodeLabels (root->left, rang + 1, dotFile, mode);
    }

    if (root->right != NULL)
    {
        treeDumpMakeNodeLabels (root->right, rang + 1, dotFile, mode);
    }

    return true;
}

bool treeDumpMakeArrows (Node *root, FILE *dotFile)
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

    return true;
}