#include "treeFileFunc.h"

bool makeTreeFromFile (const char *file, Node *root)
{
    FILE *treeFile = fopen (file, "rb");
    if (treeFile == NULL)
    {
        return false;
    }

    char *buffer = (char *)calloc (MAX_LEAF_SIZE, sizeof(char));
    if (buffer == NULL)
    {
        return false;
    }

    char *node = (char *)calloc (MAX_LEAF_SIZE, sizeof(char));
    if (node == NULL)
    {
        return false;
    }


    fgets (buffer, MAX_LEAF_SIZE, treeFile);
    while (strchr (buffer, '(') == NULL)
    {
        fgets (buffer, MAX_LEAF_SIZE, treeFile);
    }

    int size = (strrchr (buffer, '\"') - strchr (buffer, '\"') - 1);
    strncat (node, strchr (buffer, '\"') + 1, size);

    makeTreeNodesFromFile (node, buffer, root, treeFile);

    fclose (treeFile);

    return true;
}

bool makeTreeNodesFromFile (char *node, char *buffer, Node *root, FILE *treeFile)
{
    strcpy (root->data, node);

    fgets (buffer, MAX_LEAF_SIZE, treeFile);
    while (strchr (buffer, '(') == NULL)
    {
        fgets (buffer, MAX_LEAF_SIZE, treeFile);
    }

    if (strchr (buffer, '*') == NULL)
    {
        int size = strrchr (buffer, '\"') - strchr (buffer, '\"') - 1;
        *node = '\0';
        strncat (node, strchr (buffer, '\"') + 1, size);
        branchCtor (root, LEFT_NO, POISON);
        makeTreeNodesFromFile (node, buffer, root->left, treeFile);
    }

    fgets (buffer, MAX_LEAF_SIZE, treeFile);
    while (strchr (buffer, '(') == NULL)
    {
        fgets (buffer, MAX_LEAF_SIZE, treeFile);
    }

    if (strchr (buffer, '*') == NULL)
    {
        int size = strrchr (buffer, '\"') - strchr (buffer, '\"') - 1;
        *node = '\0';
        strncat (node, strchr (buffer, '\"') + 1, size);
        branchCtor (root, RIGHT_YES, POISON);
        makeTreeNodesFromFile (node, buffer, root->right, treeFile);
    }

    return true;
}