#include <stdio.h>
#include "linked_list.h"

int main(){
    
    return 0;
}

int test_peek(){
    Linked_list *lst = create_list();
    fill_list(lst);
}

void fill_list(Linked_list *lst){
    int x = 0;
    for (int i = 0; i < 10; i++){
        list_insert(&x, "int", lst);
        x++;
    }
}