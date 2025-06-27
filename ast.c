#include "ast.h"

NodeProgram *ast_build(Linked_list *lst){
    NodeProgram *program = createProgramNode(lst);

    struct Node *start = get_first(lst);
    
    //TODO ta ut main tokens innan vi börjar gå igen. DÅ kan main ligga vars som helst i filen teoretiskt.

    return program;
}

//TODO print AST needed for debugging

