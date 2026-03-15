#include <stdio.h>
#include "arraylist.h"
// gcc arraylist_init_from_demo.c arraylist.c -o init_from_demo; ./init_from_demo

void* mult_by_pi(void* v)
{
    static float  res;
    int val = *(int*)v;
    res = (float) val;
    res*=3.1415f;
    return &res;
}
void print_list(float* val){
    printf("valor novo: %f\n", *val);
}
void print_square_list_int(int* val){
    static int counter = 0;
    printf("index %d: %d\n", counter,((*val) * (*val)));
    counter++;
}
int main()
{
    int teste[] = {1,10,10,4,5};

    ArrayList* list = arraylist_init_from(teste,5,0, int);
    arraylist_foreach(list, print_square_list_int, int);

    int count_of_10 = arraylist_count(list, 10, int);
    printf("\ncontagem do 10: %d\n", count_of_10);
    printf("\nindice do 5: %d\n\n", arraylist_indexOf(list,5,int));

    ArrayList *list2 = arraylist_map(list,mult_by_pi,float);
    arraylist_foreach(list2, print_list, float);

    arraylist_free(list);
    arraylist_free(list2);

    return 0;
}