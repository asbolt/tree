#include <stdio.h>
#include <malloc.h>

int main ()
{
    char *newLeaf = (char *) calloc (150, sizeof(char));
        if (newLeaf == NULL)
        {
            return 1;
        }

        printf ("А что это?\n");
        fgets (newLeaf, 150, stdin);
        for (int numberSymbol = 0; numberSymbol < 20; numberSymbol++)
        {
            printf ("%d %c\n", numberSymbol, newLeaf[numberSymbol]);
            if (newLeaf[numberSymbol] == '\n')
            {
                printf ("ffff\n");
                newLeaf[numberSymbol] = '\0';
            }
            printf ("%d %c\n", numberSymbol, newLeaf[numberSymbol]);
        }
        printf ("%s", newLeaf);
}