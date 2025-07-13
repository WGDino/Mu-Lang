#include "ast.h"

NodeProgram *ast_build(Linked_list *lst, Arena *a){
    NodeProgram *program = createProgramNode(lst, a);

    return program;
}

//TODO print AST needed for debugging

