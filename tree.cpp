#include "tree.h"

FUNCTION_STATUS nodeCtor (Node **root, char* value)
{
    *root = (Node *)calloc (1, sizeof(Node));
    if (*root == NULL)
    {
        return ERROR;
    }

    (*root)->data = (char *)calloc (MAX_QUESTION_SIZE, sizeof(char));
    if ((*root)->data == NULL)
    {
        return ERROR;
    }

    strcpy ((*root)->data, value);
    //(*root)->data = value;

    return CORRECT;
}

FUNCTION_STATUS branchCtor (Node *node, int branch, char* value)
{
    assert (node);

    if (branch == LEFT_NO)
    {
        nodeCtor (&(node->left), value);
    } else if (branch == RIGHT_YES)
    {
        nodeCtor (&(node->right), value);
    }

    return CORRECT;
}

FUNCTION_STATUS treeAddElement (Node *node, char* value)
{
    assert (node);

    Node *currentNode = node;
    Node *previousNode = NULL;
    int branch = 0;

    while (currentNode != NULL)
    {
        previousNode = currentNode;
        branch = (value < currentNode->data)? LEFT_NO : RIGHT_YES;
        currentNode = (value < currentNode->data)? currentNode->left : currentNode->right;
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

    fprintf (logFile, "(\"%s\"\n", node->data);

    if (node->left != NULL)
    {
        print (node->left, logFile); 
    } else {
        fprintf (logFile, "(*)\n");
    }

    if (node->right != NULL)
    {
        print (node->right, logFile); 
    } else {
        fprintf (logFile, "(*)\n");
    }

    fprintf (logFile, ")\n");

    return CORRECT;
}