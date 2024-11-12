#include "tree.h"

FUNCTION_STATUS nodeCtor (Node **root, int value)
{
    *root = (Node *)calloc (1, sizeof(Node));
    if (*root == NULL)
    {
        return ERROR;
    }

    (*root)->data = value;

    return CORRECT;
}

FUNCTION_STATUS branchCtor (Node *node, int branch, int value)
{
    assert (node);

    if (branch == LEFT)
    {
        nodeCtor (&(node->left), value);
    } else if (branch == RIGHT)
    {
        nodeCtor (&(node->right), value);
    }

    return CORRECT;
}

FUNCTION_STATUS treeAddElement (Node *node, tree_element value)
{
    assert (node);

    Node *currentNode = node;
    Node *previousNode = NULL;
    int branch = 0;

    while (currentNode != NULL)
    {
        previousNode = currentNode;
        currentNode = (value < node->data)? currentNode->left : currentNode->right;
        branch = (value < node->data)? LEFT : RIGHT;
    }

    branchCtor (previousNode, branch, value);

    return CORRECT;
}

FUNCTION_STATUS treeDtor (Node *node)
{
    if (!node)
    {
        return ERROR;
    }

    if (node->left != NULL)
    {
        treeDtor (node->left); 
    }

    if (node->right != NULL)
    {
        treeDtor (node->right); 
    }

    free (node);

    return CORRECT;
}

FUNCTION_STATUS treePrint (Node *node)
{
    FILE *logFile = fopen (LOG_FILE, "wb");
    if (logFile == NULL)
    {
        return ERROR;
    }

    print (node, logFile);

    fclose (logFile);

    return CORRECT;
}

FUNCTION_STATUS print (Node *node, FILE *logFile)
{
    if (!node)
    {
        return ERROR;
    }

    fprintf (logFile, "(%d", node->data);

    if (node->left != NULL)
    {
        print (node->left, logFile); 
    } else {
        fprintf (logFile, "(*)");
    }

    if (node->right != NULL)
    {
        print (node->right, logFile); 
    } else {
        fprintf (logFile, "(*)");
    }

    fprintf (logFile, ")");

    return CORRECT;
}


FUNCTION_STATUS makeTreeFromFile (const char *file)
{
    FILE *treeFile = fopen (file, "rb");

    fseek (treeFile, 0, SEEK_END);
    int size = ftell (treeFile);
    fseek (treeFile, 0, SEEK_SET);

    char *buffer = (char *)calloc (size + 1, sizeof(char));
    if (buffer == NULL)
    {
        return ERROR;
    }

    fread (buffer, sizeof(char), size, treeFile);

    fclose (treeFile);

    //TODO
}