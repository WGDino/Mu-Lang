#include "ast_node.h"

NodeProgram *createProgramNode(){
    NodeProgram *program = malloc(sizeof(NodeProgram));
    program->main = createMainNode();
    return program;
}

NodeFunction *createMainNode() {
    NodeFunction *mainNode = malloc(sizeof(NodeFunction));
    mainNode->name = "Main";
    mainNode->returnType = TYPE_INT;
    return mainNode;
}

NodeExpr* createExprNode(){

}