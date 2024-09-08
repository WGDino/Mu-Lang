#include "linked_list.h"

int main(){
    Linked_list *lst = create_list();
    struct Node *node = get_first(lst);
    
    list_insert("hej", node);
    list_insert("ks", node);
    list_insert("asdza", node);

    print_list(lst);
}