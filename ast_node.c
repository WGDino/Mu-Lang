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

//TODO Create normal function Node

NodeStmnt *createStmntNodeDec(){
    NodeStmnt *stmnt = malloc(sizeof(NodeStmnt));
    stmnt->type = STMNT_DECLARATION;
    
    return stmnt;
}

NodeStmnt* createStmntNodeAss(NodeExpr *ident, NodeExpr *value){
    NodeStmnt *stmnt = malloc(sizeof(NodeStmnt));
    stmnt->type = STMNT_ASSIGNMENT;
    stmnt->data.assign.ident = ident;
    stmnt->data.assign.type = ident->type;
    stmnt->data.assign.value = value;
    return stmnt;
}

NodeStmnt* createStmntNodeRet(NodeExpr *expr){
    NodeStmnt *stmnt = malloc(sizeof(NodeStmnt));
    stmnt->type = STMNT_RETURN;
    stmnt->data.ret = expr;
    return stmnt;
}

NodeExpr* createExprNode(Token *token, int type){
    NodeExpr *expr = malloc(sizeof(NodeExpr));
    expr->type = type;

    switch (expr->type){
    case EXPR_INT_LITERAL:
        expr->data.int_literal.intValue = tokenGetInt(token);
        break;
    
    case EXPR_VARIABLE:
        expr->data.identifier.varName = token->data;
        break;
    
    case EXPR_FLOAT_LITERAL:

        break;

    case EXPR_CHAR_LITERAL:

        break;

    case EXPR_FUNCTION_CALL:
        
        break;

    case EXPR_STRING_LITERAL:
        break;

    default:
        break;
    }

    return expr;
}