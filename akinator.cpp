#include "akinator.h"

FUNCTION_STATUS akinator (Node *node) 
{// TODO вводить несколько слов
    assert (node);

    Node *currentNode = node;

    while (currentNode->left != NULL && currentNode->right != NULL)
    {
        printf ("%s\n", currentNode->data);
        char *answer = (char *)calloc (MAX_ANSWER_SIZE, sizeof(char));
        scanf ("%s", answer);

        if (strcmp(answer, "нет") == 0)
        {
            currentNode = currentNode->left;
        } else if (strcmp(answer, "да") == 0)
        {
            currentNode = currentNode->right;
        }
    }

    printf ("Это %s?\n", currentNode->data);
    char *answer = (char *)calloc (MAX_ANSWER_SIZE, sizeof(char));
    if (answer == NULL)
    {
        return ERROR;
    }
    scanf ("%s", answer);

    if (strcmp(answer, "нет") == 0)
    {
        char *oldLeaf = (char *) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (oldLeaf == NULL)
        {
            return ERROR;
        }
        
        oldLeaf = currentNode->data;

        char *newLeaf = (char *) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (newLeaf == NULL)
        {
            return ERROR;
        }

        printf ("А что это?\n");
        scanf ("%s", newLeaf);

        char *newQuestion = (char *) calloc (MAX_QUESTION_SIZE, sizeof(char));
        if (newQuestion == NULL)
        {
            return ERROR;
        }

        printf ("Чем %s отличается от %s? %s...\n", newLeaf, oldLeaf, newLeaf);
        scanf ("%s", newQuestion);

        strcat (newQuestion, "?");
        currentNode->data = newQuestion;
        branchCtor (currentNode, LEFT_NO, oldLeaf);
        branchCtor (currentNode, RIGHT_YES, newLeaf);

    } else if (strcmp(answer, "да") == 0)
    {
        printf ("бимбамбимбум\n");
    }

    return CORRECT;
}