#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "token_types.h"
#include "linked_list.h"
#include "tokenizer.h"
#include "ast.h"

/*DO these before continuing work elsewhere*/
//TODO AST 
//TODO Create assignment operator like + and -
//TODO Create NodeStmnt

/* DO these when time is found or when they are "reached"*/
//TODO investigate if we want NodeStmnt to have tokens with type and 
//TODO ident in it or seperate field for them both using char * and a typekind?
//TODO think about how we want to make assignment work with stmnt node encapsulating exprNodes etc
//TODO swap current setup for is_keyword(DONE) and is_operator.
//TODO add types for nodes in AST
//TODO AST BUILDING
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
    
    //print_list(lst, print_token);
    
    NodeProgram *prog = ast_build(lst);

    list_remove(lst);
    tt_remove(tt);

    return 0;
}