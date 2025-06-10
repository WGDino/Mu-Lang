#include "ast_node.h"

NodeProgram *createProgramNode(Linked_list *lst){
    NodeProgram *program = malloc(sizeof(NodeProgram));
    program->main = createMainNode(lst);
    return program;
}

NodeFunction *createMainNode(Linked_list *lst) {//TODO error handle this
    NodeFunction *mainNode = malloc(sizeof(NodeFunction));
    mainNode->name = "Main";
    int x = peek_until("main", lst);//TODO this will not work if we have variables named main_node lets say. Probs add _ in alpha_num
    
    Token *data = peek(x, lst);
    if(strcmp(data->data, "main") == 0){
        consume(x, lst);
    }

    else{
        perror("Main not found!");
        return NULL;
    }

    data = peek(x, lst);
    if(strcmp(data->data, "(") == 0){
        consume(x, lst);
    }

    else{
        perror("Main function structure!");
        return NULL;
    }

    data = peek(x, lst);
    if(strcmp(data->data, "int") == 0){
        consume(x, lst);
        mainNode->returnType = TYPE_INT;
    }

    data = peek(x, lst);
    if(strcmp(data->data, ",") == 0){
        //TODO handle args to main here
    }

    else if(strcmp(data->data, ")") == 0){
        consume(x, lst);
    }

    data = peek(x, lst);
    if(strcmp(data->data, "{") == 0){
        consume(x, lst);
    }

    Token *tok = peek(x, lst);
    while ( strcmp(tok->data, "}") != 0){
        if(strcmp(tok->type, "Type") == 0){
            if(strcmp(tok->data, "int") == 0){
                TypeKind type = TYPE_INT;
                consume(x, lst);
                tok = peek(x, lst);
                if(strcmp(tok->data, "Identifier") == 0){
                    NodeExpr *ident = createExprNode(tok, EXPR_VARIABLE);
                    consume(x, lst);
                    tok = peek(x, lst);
                    if(strcmp(tok->data, "=") == 0){
                        //TODO parse assignment value here
                    }

                    else if(strcmp(tok->data, ";") == 0){
                        //TODO transition to next line here
                    }
                }

                else{
                    perror("Expected Identifier!");
                    return NULL;
                }
            }
        }

        else if(strcmp(tok->type, "Identifier") == 0){

        }

        else if(strcmp(tok->type, "Keyword") == 0){

        }
        
        tok = peek(x, lst);
        break;
    }
    

    printf("%d\n", x);
    return mainNode;
}



//TODO Create normal function Node

NodeStmnt *createStmntNodeDec(TypeKind type, NodeExpr *ident){
    NodeStmnt *stmnt = malloc(sizeof(NodeStmnt));
    stmnt->type = STMNT_DECLARATION;
    stmnt->data.declaration.type = type;
    stmnt->data.declaration.ident = ident;
    
    return stmnt;
}

NodeStmnt* createStmntNodeAss(TypeKind type, NodeExpr *ident, NodeExpr *value){
    NodeStmnt *stmnt = malloc(sizeof(NodeStmnt));
    stmnt->type = STMNT_ASSIGNMENT;
    stmnt->data.assign.ident = ident;
    stmnt->data.assign.type = type;
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