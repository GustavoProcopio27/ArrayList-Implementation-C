#include <stdio.h>
#include "arraylist.h"
// gcc arraylist_demo.c arraylist.c -o demo; ./demo
typedef char* string; // Seria tão agravel se criassem um desse na porra da string.h

int main()
{
    string str = "teste de cria1";
    ArrayList *list = arraylist_init(string);
    arraylist_add(list, str, string);
    arraylist_add(list, "teste de cria2", string);
    arraylist_add(list, "teste de cria3", string);

    printf("%s\n", arraylist_get(list,0, string));

    string* popped = arraylist_pop(list, 1,string);
    printf("O tamanho atual eh: %zu\n e o elemento retirado foi (%s)\n\n", list->length, *popped);

    for(int i =0;i<list->length;i++)
    {
        printf("Elementos restantes: (%s)\n", arraylist_get(list,i,string));
    }
    arraylist_free(list); // Não esqueça disso
    free(popped);
    
    return 0;
}