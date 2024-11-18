#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "token_types.h"
#include "linked_list.h"
#include "tokenizer.h"

//TODO insert consume and peek into linked_list_print
//TODO errorcheck list remove
//TODO swap current setup for is_keyword and so forth.
//TODO add same checking for operators
//TODO add types for nodes in AST
//TODO AST BUILDING
//TODO update_token_type use length
//TODO split ast_node into more classes

int main(int argc, char *argv[]){
    Linked_list *lst = create_list();
    Token_types *tt = token_types_create();

    if(argc != 2 ){
        printf("Wrong Usage.\n Correct usage is muc <input.mu>\n");
    }

    else{
        printf("Lexical analysis starting\n");
        token_reader(argv[1], lst, tt);
    }
    
    print_list(lst);
    list_remove(lst);
    tt_remove(tt);

    return 0;
}