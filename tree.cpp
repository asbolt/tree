#include "tree.h"

bool nodeCtor (Node **root, const char* value, Node *parent)
{
    assert (root);
    assert (value);

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

bool branchCtor (Node *node, int branch, const char* value)
{
    assert (node);
    assert (value);

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
    assert (value);

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
    assert (node);

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
    assert (node);
    assert (node->data);

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
    assert (logFile);
    checkForErrors (node);

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
    assert (data);
    assert (root);
    assert (root->data);
    assert (node);
    assert (way);

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

TREE_ERRORS checkForErrors (Node *root)
{
    if (root == NULL)
    {
        return TREE_NULL;
    }

    if (root->data == NULL)
    {
        return TREE_DATA_NULL;
    }

    return TREE_GOOD;
}