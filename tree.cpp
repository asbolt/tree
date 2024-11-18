#include "tree.h"

bool nodeCtor (Node **root, char* value, Node *parent)
{
    *root = (Node *)calloc (1, sizeof(Node));
    if (*root == NULL)
    {
        return false;
    }

    (*root)->data = (char *)calloc (MAX_LEAF_SIZE, sizeof(char));
    if ((*root)->data == NULL)
    {
        return false;
    }

    (*root)->parent = parent;

    strcpy ((*root)->data, value);

    return true;
}

bool branchCtor (Node *node, int branch, char* value)
{
    assert (node);

    if (branch == LEFT_NO)
    {
        nodeCtor (&(node->left), value, node);
    } else if (branch == RIGHT_YES)
    {
        nodeCtor (&(node->right), value, node);
    }

    return true;
}

bool treeAddElement (Node *node, char* value)
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

    return true;
}

bool treeDtor (Node *node)
{
    if (!node)
    {
        return false;
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

    return true;
}

bool treePrint (Node *node)
{
    FILE *logFile = fopen (LOG_FILE, "wb");
    if (logFile == NULL)
    {
        return false;
    }

    print (node, logFile);

    fclose (logFile);

    return true;
}

bool print (Node *node, FILE *logFile)
{
    if (!node)
    {
        return false;
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

    return true;
}

Node *findElement (char *data, Node *root, Node *node, int *way, int ind)
{
    if (strcmp (node->data, data) == 0)
    {
        return node;
    }

    if (node->left != NULL)
    {
        way[ind] = LEFT_NO;

        if (findElement (data, root, node->left, way, ind + 1) != NULL)
        {
            return findElement (data, root, node->left, way, ind + 1);
        }

        way[ind] = 0;
    }

    if (node->right != NULL)
    {
        way[ind] = RIGHT_YES;

        if (findElement (data, root, node->right, way, ind + 1) != NULL)
        {
            return findElement (data, root, node->right, way, ind + 1);
        }

        way[ind] = 0;
    }

    return NULL;
}