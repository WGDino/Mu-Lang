#include "ast.h"

NodeProgram *ast_build(Linked_list *lst){
    NodeProgram *program = createProgramNode();

    struct Node *start = get_first(lst);
    while(start != get_head(lst)){
        
    }   
}