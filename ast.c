#include "ast.h"

NodeProgram *ast_build(Linked_list *lst){
    NodeProgram *program = createProgramNode();

    struct Node *start = get_first(lst);
    int x = peek_until("{", lst);
    printf("%d\n", x);
    while(start != get_head(lst)){
        break;
    }

    return program;
}

