#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "token_types.h"
#include "linked_list.h"
#include "tokenizer.h"
#include "ast.h"

/* AST */
//TODO Create assignment operator like + and -
//TODO Create NodeStmnt
//TODO complete parsing and then test print_ast

/* DO these when time is found or when they are "reached"*/
//TODO swap current setup for is_keyword(DONE) and is_operator.
//TODO add types for nodes in AST

//TODO Symbol table for keeping track of used varaible names in scope
//TODO Rework to exclude strcmp in AST-building
//TODO might need to free each node after consume in AST

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
    
    //print_list(lst, print_token);
    
    NodeProgram *prog = ast_build(lst);
    print_list(lst, print_token);
    list_remove(lst);
    tt_remove(tt);

    return 0;
}