#include "akinator.h"

bool guessElement (Node *node) 
{
    assert (node);
    assert(node->data);

    Node *currentNode = node;

    findLeafElement (&currentNode);

    printf ("Это %s?\n", currentNode->data);
    char answer [MAX_ANSWER_SIZE] = {};
    fgets (answer, MAX_ANSWER_SIZE, stdin);

    if (strstr(answer, "нет") != 0 || strstr(answer, "Нет") != 0)
    {
        char *oldLeaf = (char *) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (oldLeaf == NULL)
        {
            return false;
        }

        strcpy (oldLeaf, currentNode->data);

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
        strcpy (currentNode->data, newQuestion);
        branchCtor (currentNode, LEFT_NO, oldLeaf);
        branchCtor (currentNode, RIGHT_YES, newLeaf);

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
    char answer[MAX_ANSWER_SIZE] = {};

    while ((*currentNode)->left != NULL && (*currentNode)->right != NULL)
    {
        printf ("%s\n", (*currentNode)->data);
        fgets (answer, MAX_ANSWER_SIZE, stdin);

        if (strstr(answer, "нет") != 0 || strstr(answer, "Нет") != 0)
        {
            (*currentNode) = (*currentNode)->left;
        } else if (strstr(answer, "да") != 0 || strstr(answer, "Да") != 0)
        {
            (*currentNode) = (*currentNode)->right;
        } else {
            return false;
        }
    }

    return true;
}

bool getElement (char *element)
{
    assert (element);

    fgets (element, MAX_LEAF_SIZE, stdin);
    for (int numberSymbol = 0; numberSymbol < MAX_LEAF_SIZE; numberSymbol++)
    {
        if (element[numberSymbol] == '\n')
        {
            element[numberSymbol] = '\0';
            return true;
        }
    }

    return false;
}

bool giveDefinition (char *data, Node *root)
{
    assert (data);
    assert (root);
    assert (root->data);

    int way [MAX_WAY_SIZE] = {};
    int ind = 0;

    findElement (data, root, root, way, ind);

    printf ("%s -- это", data);

    for (ind = 0; way[ind] != 0; ind++)
    {
        if (way[ind] == LEFT_NO)
        {
            char partDefinition [MAX_LEAF_SIZE] = {0};
            char *question = strchr(root->data, '?');
            int size = (question - root->data)/sizeof(char);
            strncat (partDefinition, root->data, size);

            printf (" НЕ %s", partDefinition);
            root = root->left; 
        }

        if (way[ind] == RIGHT_YES)
        {
            char partDefinition [MAX_LEAF_SIZE] = {0};
            char *question = strchr(root->data, '?');
            int size = (question - root->data)/sizeof(char);
            strncat (partDefinition, root->data, size);

            printf (" %s", partDefinition);
            root = root->right; 
        }
    }

    printf (".\n");

    return true;
}

bool findDifferences (char *dataFirst, char *dataSecond, Node *root)
{
    assert (dataFirst);
    assert (dataSecond);
    assert (root);
    assert (root->data);

    int wayFirst [MAX_WAY_SIZE] = {};
    int waySecond [MAX_WAY_SIZE] = {};

    int ind = 0;

    findElement (dataFirst, root, root, wayFirst, ind);
    findElement (dataSecond, root, root, waySecond, ind);

    printf ("%s и %s похожи тем, что они оба", dataFirst, dataSecond);

    for (ind = 0; wayFirst[ind] == waySecond[ind] != 0; ind++)
    {
        if (wayFirst[ind] == LEFT_NO)
        {
            char partDefinition [MAX_LEAF_SIZE] = {0};
            char *question = strchr(root->data, '?');
            int size = (question - root->data)/sizeof(char);
            strncat (partDefinition, root->data, size);

            printf (" НЕ %s", partDefinition);
            root = root->left;
        }

        if (wayFirst[ind] == RIGHT_YES)
        {
            char partDefinition [MAX_LEAF_SIZE] = {0};
            char *question = strchr(root->data, '?');
            int size = (question - root->data)/sizeof(char);
            strncat (partDefinition, root->data, size);

            printf (" %s", partDefinition);
            root = root->right;
        }
    }
    printf (".\n");

    if (wayFirst[ind] == LEFT_NO)
    {
        char partDefinition [MAX_LEAF_SIZE] = {0};
        char *question = strchr(root->data, '?');
        int size = (question - root->data)/sizeof(char);
        strncat (partDefinition, root->data, size);

        printf ("Но %s НЕ %s.\n", dataFirst, partDefinition);
    }

    if (wayFirst[ind] == RIGHT_YES)
    {
        char partDefinition [MAX_LEAF_SIZE] = {0};
        char *question = strchr(root->data, '?');
        int size = (question - root->data)/sizeof(char);
        strncat (partDefinition, root->data, size);
        
        printf ("Но %s %s.\n", dataFirst, partDefinition);
    }

    return true;
}

bool akinator (Node *root)
{
    checkForErrors (root);

    printf ("Выберите режим: угадать элемент, дать определение или найти различия [уэ\\до\\нр]\n");
    char answer [MAX_ANSWER_SIZE] = {0};
    fgets (answer, MAX_ANSWER_SIZE, stdin);

    if (strcmp (answer, "уэ\n") == 0)
    {
        guessElement (root);
    } else if (strcmp (answer, "до\n") == 0)
    {
        char *leaf = (char*) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (leaf == NULL)
        {
            return false;
        }

        printf ("Слово: \n");
        fgets (leaf, MAX_LEAF_SIZE, stdin);

        giveDefinition (leaf, root);
    } else if (strcmp (answer, "нр\n") == 0)
    {
        char *leafFirst = (char*) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (leafFirst == NULL)
        {
            return false;
        }

        char *leafSecond = (char*) calloc (MAX_LEAF_SIZE, sizeof(char));
        if (leafSecond == NULL)
        {
            return false;
        }

        printf ("Слова:\n");
        fgets (leafFirst, MAX_LEAF_SIZE, stdin);
        fgets (leafSecond, MAX_LEAF_SIZE, stdin);

        findDifferences (leafFirst, leafSecond, root);
    } else {
        printf ("Syntax error\n");
        return false;
    }

    return true;
}