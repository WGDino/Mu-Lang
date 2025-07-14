#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "token_types.h"
#include "linked_list.h"
#include "tokenizer.h"
#include "ast.h"
#include "code_generation.h"

/* AST */
//TODO improve printing of ast to include heirarchy and tree structure

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

    Arena arena = arena_create(1024*1024*8);
    NodeProgram *prog = ast_build(lst, &arena);
    
    print_ast(prog->main, 1);
    print_list(lst, print_token);
    list_remove(lst);
    tt_remove(tt);
    gen_code(prog);
    arena_free(&arena);
    //TODO generate asm-code to run using MASM
    return 0;
}