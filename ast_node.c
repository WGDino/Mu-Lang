#include "ast_node.h"

NodeProgram *createProgramNode(Linked_list *lst, Arena *a){//4 mb
    NodeProgram *program = (NodeProgram *) arena_alloc(a, sizeof(NodeProgram));
    program->main = createMainNode(lst, a);
    return program;
}

NodeFunction *createMainNode(Linked_list *lst, Arena *a) {//TODO error handle this
    NodeFunction *mainNode = (NodeFunction *) arena_alloc(a, sizeof(NodeFunction));
    mainNode->name = "Main";
    mainNode->children = create_list();
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
    int is_var = 0;
    while ( strcmp(tok->data, "}") != 0){
        if(strcmp(tok->type, "Type") == 0){
            NodeStmnt *decl;
            if(strcmp(tok->data, "int") == 0){
                TypeKind type = TYPE_INT;
                consume(x, lst);
                tok = peek(x, lst);
                if(strcmp(tok->type, "Identifier") == 0){
                    NodeExpr *ident = createExprNode(tok, EXPR_VARIABLE, a);
                    consume(x, lst);
                    tok = peek(x, lst);
                    NodeExpr *value = NULL;
                    if(strcmp(tok->data, "=") == 0){
                        consume(x, lst);
                        value = parse_expr(0, lst, x, a, &is_var);
                    }

                    else if(strcmp(tok->data, ";") == 0){
                        consume(x, lst);
                    }

                    decl = createStmntNodeDec(type, ident, a, is_var);
                    mainNode->ints++;
                    if(value != NULL){
                        decl->data.declaration.value = value;
                    }
                }

                else{
                    perror("Expected Identifier!");
                    return NULL;
                }
            }
            
            struct Node *pos = get_head(mainNode->children);
            list_insert(decl, "stmnt", pos);
        }

        else if(strcmp(tok->type, "Identifier") == 0){
            //TODO this third
        }

        else if(strcmp(tok->type, "Keyword") == 0){
            //TODO this next since return is a keyword
            if(strcmp(tok->data, "return") == 0){//TODO rework this to be in a loop to parse expression returns + use constant folding checks
                consume(x, lst);
                tok = peek(x, lst);
                NodeExpr *expr;
                if(strcmp(tok->type, "Identifier") == 0){
                    expr = createExprNode(tok, EXPR_VARIABLE, a);
                    consume(x, lst);
                }

                else if(strcmp(tok->type, "Int_lit") == 0){
                    expr = createExprNode(tok, EXPR_INT_LITERAL, a);
                    consume(x, lst);
                }

                NodeStmnt *ret = createStmntNodeRet(expr, a, is_var);
                struct Node *pos = get_head(mainNode->children);
                list_insert(ret, "stmnt", pos);
            }

        }
        
        tok = peek(x, lst);
        if(strcmp(tok->data, ";") == 0){
            consume(x, lst);
        }
        
    }
    consume(x, lst);
    return mainNode;
}

NodeExpr *parse_expr(int presedence, Linked_list *lst, int offset, Arena *a, int *is_var){
    Token *data = peek(offset, lst);
    if(!get_is_operator(data)){
        consume(offset, lst);
    }

    else{
        perror("Unable to parse expression!");
    }

    if(*is_var == 0 && strcmp(data->type, "Identifier") == 0){
        *is_var = 1;
    }

    NodeExpr *lhs = createExprNode(data, EXPR_INT_LITERAL, a);

    while(true){
        Token *next = peek(offset, lst);

        if(*is_var == 0 && strcmp(next->type, "Identifier") == 0){
            *is_var = 1;
        }

        int pres = check_presedence(next);
        if(presedence >= pres){
            return lhs;
        }

        else{
            char *operator = next->data;
            consume(offset, lst);
            //TODO CHECK if it is an operator
            NodeExpr *rhs = parse_expr(pres + 1, lst, offset, a, is_var);
            //TODO error check rhs
            
            NodeExpr *binaryop  = createExprNode(next, EXPR_BINARY_OP, a);
            if(strcmp(binaryop->data.binaryOp.oper, "0") == 0){
                binaryop->data.binaryOp.left = lhs;
                binaryop->data.binaryOp.oper = operator;
                binaryop->data.binaryOp.right = rhs;
                return binaryop;
            }
        }
    }

    if(strcmp(data->data, ";") == 0){
        return NULL;
    }

    return NULL;
}

int check_presedence(Token *data){
    if(strcmp(data->data, "+") == 0 || strcmp(data->data, "-") == 0){
        return 1;
    }

    else if(strcmp(data->data, "*") == 0 || strcmp(data->data, "/") == 0){
        return 2;
    }

    else{
        return 0;
    }
}

//TODO Create normal function Node

NodeStmnt *createStmntNodeDec(TypeKind type, NodeExpr *ident, Arena *a, int is_const){
    NodeStmnt *stmnt = (NodeStmnt *) arena_alloc(a, sizeof(NodeStmnt));
    stmnt->type = STMNT_DECLARATION;
    stmnt->data.declaration.type = type;
    stmnt->data.declaration.ident = ident;
    stmnt->is_const = is_const;
    
    return stmnt;
}

NodeStmnt* createStmntNodeAss(TypeKind type, NodeExpr *ident, NodeExpr *value, Arena *a, int is_const){
    NodeStmnt *stmnt = (NodeStmnt *) arena_alloc(a, sizeof(NodeStmnt));
    stmnt->type = STMNT_ASSIGNMENT;
    stmnt->data.assign.ident = ident;
    stmnt->data.assign.type = type;
    stmnt->data.assign.value = value;
    stmnt->is_const = is_const;

    return stmnt;
}

NodeStmnt* createStmntNodeRet(NodeExpr *expr, Arena *a, int is_const){
    NodeStmnt *stmnt = (NodeStmnt *) arena_alloc(a, sizeof(NodeStmnt));
    stmnt->type = STMNT_RETURN;
    stmnt->data.ret = expr;
    stmnt->is_const = is_const;

    return stmnt;
}

NodeExpr* createExprNode(Token *token, int type, Arena *a){
    NodeExpr *expr = (NodeExpr *) arena_alloc(a, sizeof(NodeExpr));//
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
    
    case EXPR_BINARY_OP:
        expr->data.binaryOp.oper = "0";
        break;
    default:
        break;
    }

    return expr;
}

void print_ast(NodeFunction *root, int type){
    printf("PRINTING\n");
    if (type == 0){
        struct Node *head = get_head(root->children);
        struct Node *walk = get_first(root->children);

        while(walk != head){
            NodeStmnt *stmnt = (NodeStmnt *) walk;
            print_stmnt(stmnt);
            walk = walk->next;
        }
    }

    else if(type == 1){
        //TODO print if root is main or smth else having functions as children
        struct Node *head = get_head(root->children);
        struct Node *walk = get_first(root->children);

        while(walk != head){
            if(strcmp(walk->data_type, "func") == 0){
                NodeFunction *func = (NodeFunction *) walk->data;
                print_ast(func, 1); //We write type 1 since we cannot know and this is secure for now
                walk = walk->next;
            }

            else if(strcmp(walk->data_type, "stmnt") == 0){
                NodeStmnt *stmnt = (NodeStmnt *) walk->data;
                print_stmnt(stmnt);
                walk = walk->next;   
            }
        }
    }
    
}

void print_stmnt(NodeStmnt *stmtn){
    if(stmtn->type == STMNT_ASSIGNMENT){
        printf("ASSIGN\n");
        print_expr(stmtn->data.assign.ident);
        print_expr(stmtn->data.assign.value);
        printf("\n");
    }

    else if(stmtn->type == STMNT_DECLARATION){
        printf("DECLARE\n");
        print_expr(stmtn->data.declaration.ident);
        printf(" = ");
        print_expr(stmtn->data.declaration.value);
        printf("\n");
    }

    else if(stmtn->type == STMNT_RETURN){
        printf("RETURN\n");
        print_expr(stmtn->data.ret);
        printf("\n");
    }
}

void print_expr(NodeExpr *expr){
    if(expr->type == EXPR_INT_LITERAL){
        printf("%d", expr->data.int_literal.intValue);
    }

    else if(expr->type == EXPR_FLOAT_LITERAL){
        printf("%f", expr->data.float_literal.floatValue);
    }

    else if(expr->type == EXPR_STRING_LITERAL){
        printf("%s", expr->data.string_literal.stringValue);
    }

    else if(expr->type == EXPR_CHAR_LITERAL){
        printf("%c", expr->data.char_literal.charValue);
    }

    else if(expr->type == EXPR_BINARY_OP){
        print_expr(expr->data.binaryOp.left);
        printf("%s", expr->data.binaryOp.oper);
        print_expr(expr->data.binaryOp.right);
    }

    else if(expr->type == EXPR_VARIABLE){
        printf("%s", expr->data.identifier.varName);
    }

    else if(expr->type == EXPR_FUNCTION_CALL){
        //TODO this seems weird and should probs not be here but who knows.
        //TODO maybe we do another call to print_ast here?
    }
}