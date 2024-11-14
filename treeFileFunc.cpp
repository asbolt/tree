#include "treeFileFunc.h"

FUNCTION_STATUS makeTreeFromFile (const char *file, Node *root)
{
    FILE *treeFile = fopen (file, "rb");
    if (treeFile == NULL)
    {
        return ERROR;
    }

    char *buffer = (char *)calloc (MAX_QUESTION_SIZE, sizeof(char));
    if (buffer == NULL)
    {
        return ERROR;
    }

    char *node = (char *)calloc (MAX_QUESTION_SIZE, sizeof(char));
    if (node == NULL)
    {
        return ERROR;
    }


    fgets (buffer, MAX_QUESTION_SIZE, treeFile);
    while (strchr (buffer, '(') == NULL)
    {
        fgets (buffer, MAX_QUESTION_SIZE, treeFile);
    }

    int size = (strrchr (buffer, '\"') - strchr (buffer, '\"') - 1);
    strncat (node, strchr (buffer, '\"') + 1, size);

    makeTreeNodesFromFile (node, buffer, root, treeFile);

    fclose (treeFile);

    return CORRECT;
}

FUNCTION_STATUS makeTreeNodesFromFile (char *node, char *buffer, Node *root, FILE *treeFile)
{
    strcpy (root->data, node);

    fgets (buffer, MAX_QUESTION_SIZE, treeFile);
    while (strchr (buffer, '(') == NULL)
    {
        fgets (buffer, MAX_QUESTION_SIZE, treeFile);
    }

    if (strchr (buffer, '*') == NULL)
    {
        int size = strrchr (buffer, '\"') - strchr (buffer, '\"') - 1;
        *node = '\0';
        strncat (node, strchr (buffer, '\"') + 1, size);
        branchCtor (root, LEFT_NO, POISON);
        makeTreeNodesFromFile (node, buffer, root->left, treeFile);
    }

    fgets (buffer, MAX_QUESTION_SIZE, treeFile);
    while (strchr (buffer, '(') == NULL)
    {
        fgets (buffer, MAX_QUESTION_SIZE, treeFile);
    }

    if (strchr (buffer, '*') == NULL)
    {
        int size = strrchr (buffer, '\"') - strchr (buffer, '\"') - 1;
        *node = '\0';
        strncat (node, strchr (buffer, '\"') + 1, size);
        branchCtor (root, RIGHT_YES, POISON);
        makeTreeNodesFromFile (node, buffer, root->right, treeFile);
    }

    return CORRECT;
}