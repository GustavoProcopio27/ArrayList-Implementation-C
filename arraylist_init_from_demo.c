#include <stdio.h>
#include "arraylist.h"
// gcc arraylist_init_from_demo.c arraylist.c -o init_from_demo; ./init_from_demo

int main()
{
    int teste[] = {1,10,10,4,5};

    ArrayList* list = arraylist_init_from(teste,5,0, int);
    for(int i = 0;i<5;i++)
    {
        printf("index %d: %d\n", i , arraylist_get(list,i,int));
    }
    int count_of_10 = arraylist_count(list, 10, int);
    printf("contagem do 10: %d\n", count_of_10);
    printf("indice do 5: %d\n", arraylist_indexOf(list,5,int));

    arraylist_free(list);

    return 0;
}