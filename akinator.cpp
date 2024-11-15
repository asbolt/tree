#include "akinator.h"

bool guessElement (Node *node) 
{
    assert (node);

    Node *currentNode = node;

    findLeafElement (&currentNode);

    printf ("Это %s?\n", currentNode->data);
    char *answer = (char *)calloc (MAX_ANSWER_SIZE, sizeof(char));
    if (answer == NULL)
    {
        return false;
    }
    fgets (answer, MAX_ANSWER_SIZE, stdin);

    if (strstr(answer, "нет") != 0 || strstr(answer, "Нет") != 0)
    {
        char *oldLeaf = (char *) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (oldLeaf == NULL)
        {
            return false;
        }
        
        oldLeaf = currentNode->data;

        char *newLeaf = (char *) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (newLeaf == NULL)
        {
            return false;
        }

        printf ("А кто это?\n");
        getElement (newLeaf);

        char *newQuestion = (char *) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (newQuestion == NULL)
        {
            return false;
        }

        printf ("Чем %s отличается от %s? %s...\n", newLeaf, oldLeaf, newLeaf);
        getElement (newQuestion);

        strcat (newQuestion, "?");
        currentNode->data = newQuestion;
        branchCtor (currentNode, LEFT_NO, oldLeaf);
        branchCtor (currentNode, RIGHT_YES, newLeaf);

        free (answer);
        free (newLeaf);
        free (oldLeaf);
        free (newQuestion);

    } else if (strstr(answer, "да") != 0 || strstr(answer, "Да") != 0)
    {
        printf ("бимбамбимбум\n");
    }

    return true;
}

bool findLeafElement (Node **currentNode)
{
    while ((*currentNode)->left != NULL && (*currentNode)->right != NULL)
    {
        printf ("%s\n", (*currentNode)->data);

        char *answer = (char *)calloc (MAX_ANSWER_SIZE, sizeof(char));
        if (answer == NULL)
        {
            return false;
        }

        fgets (answer, MAX_ANSWER_SIZE, stdin);

        if (strstr(answer, "нет") != 0 || strstr(answer, "Нет") != 0)
        {
            (*currentNode) = (*currentNode)->left;
        } else if (strstr(answer, "да") != 0 || strstr(answer, "Да") != 0)
        {
            (*currentNode) = (*currentNode)->right;
        }

        free (answer);
    }

    return true;
}

bool getElement (char *element)
{
    fgets (element, MAX_LEAF_SIZE, stdin);
    for (int numberSymbol = 0; numberSymbol < MAX_LEAF_SIZE; numberSymbol++)
    {
        if (element[numberSymbol] == '\n')
        {
            element[numberSymbol] = '\0';
        }
    }

    return true;
}