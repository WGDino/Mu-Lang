#include "ast.h"

NodeProgram *ast_build(Linked_list *lst){
    NodeProgram *program = createProgramNode(lst);

    return program;
}

//TODO print AST needed for debugging

