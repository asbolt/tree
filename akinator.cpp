#include "akinator.h"

FUNCTION_STATUS akinator (Node *node) 
{
    assert (node);

    Node *currentNode = node;

    while (currentNode->left != NULL && currentNode->right != NULL)
    {
        printf ("%s\n", currentNode->data);
        char *answer = (char *)calloc (MAX_ANSWER_SIZE, sizeof(char));
        fgets (answer, MAX_ANSWER_SIZE, stdin);

        if (strstr(answer, "нет") != 0 || strstr(answer, "Нет") != 0)
        {
            currentNode = currentNode->left;
        } else if (strstr(answer, "да") != 0 || strstr(answer, "Да") != 0)
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
    fgets (answer, MAX_ANSWER_SIZE, stdin);

    if (strstr(answer, "нет") != 0 || strstr(answer, "Нет") != 0)
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

        printf ("А кто это?\n");
        fgets (newLeaf, MAX_QUESTION_SIZE, stdin);
        for (int numberSymbol = 0; numberSymbol < MAX_QUESTION_SIZE; numberSymbol++)
        {
            if (newLeaf[numberSymbol] == '\n')
            {
                newLeaf[numberSymbol] = '\0';
            }
        }

        char *newQuestion = (char *) calloc (MAX_QUESTION_SIZE, sizeof(char));
        if (newQuestion == NULL)
        {
            return ERROR;
        }

        printf ("Чем %s отличается от %s? %s...\n", newLeaf, oldLeaf, newLeaf);
        fgets (newQuestion, MAX_QUESTION_SIZE, stdin);
        for (int numberSymbol = 0; numberSymbol < MAX_QUESTION_SIZE; numberSymbol++)
        {
            if (newQuestion[numberSymbol] == '\n')
            {
                newQuestion[numberSymbol] = '\0';
            }
        }

        strcat (newQuestion, "?");
        currentNode->data = newQuestion;
        branchCtor (currentNode, LEFT_NO, oldLeaf);
        branchCtor (currentNode, RIGHT_YES, newLeaf);

    } else if (strstr(answer, "да") != 0 || strstr(answer, "Да") != 0)
    {
        printf ("бимбамбимбум\n");
    }

    return CORRECT;
}