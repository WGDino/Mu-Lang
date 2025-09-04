#include "code_generation.h"

void gen_code(NodeProgram *prog){
    FILE *out = fopen("muc_out.asm", "w");

    if(get_os() == 1){//Windows
        gen_windows(out, prog);
        fclose(out);
        run_windows();
    }

    else if(get_os() == 2){//linux
        gen_linux(out);
        //run_linux
        fclose(out);
    }

    else { //unkown
        perror("Unknown OS! -- Fuck you mac!");
    }
    printf("Build Complete!\n");
    printf("USE: ./muc_out.exe\necho $LASTEXITCODE");
}

void run_windows(){
    int result = system("nasm -f win64 muc_out.asm -o muc_out.obj");

    if(result != 0){
        perror("Nasm failed!\n");
    }

    result = system("gcc -mconsole muc_out.obj -o muc_out.exe -lkernel32");

    if(result != 0){
        perror("LINK failed!\n");
    }

}

void gen_windows(FILE *out, NodeProgram *prog){
    win_boiler(out);
    Hashtable *hash = create_hashtable(100);
    NodeFunction *main_node = prog->main;

    struct Node *head = get_head(main_node->children);
    struct Node *walk = get_first(main_node->children);
    fprintf(out, "    push rbp\n");
    fprintf(out, "    mov rbp, rsp\n");
    fprintf(out, "    sub rsp, %lld\n", 8*main_node->ints + 32);
    int count_ints = 1;//TODO change this to something smarter l8r

    while(walk != head){
        if(strcmp(walk->data_type, "func") == 0){
            //TODO fix this later
        }

        else if(strcmp(walk->data_type, "stmnt") == 0){
            NodeStmnt *stmnt = (NodeStmnt *) walk->data;
            if(stmnt->is_const == 0){//0 here means it is const for some stupid reason
                const_stmnt(stmnt, out, hash, &count_ints);
            }

            else{//statement contains variables which can not be resolved early
                var_stmnt(stmnt, out, hash, &count_ints);
            }
                
            walk = walk->next;   
        }
    }
    
    win_boiler2(out);
}

void *var_expr(NodeExpr *expr, FILE *out, int *count, Hashtable *hash){
    if(expr->type == EXPR_BINARY_OP){
        void *left = var_expr(expr->data.binaryOp.left, out, count, hash);//TODO error check this somehow mbe change to int
        void *right = var_expr(expr->data.binaryOp.right, out, count, hash);

        var_expr_math(expr, out, count, hash);
    }

    else if(expr->type == EXPR_INT_LITERAL){
        return NULL;
    }

    return NULL;
}

void var_expr_math(NodeExpr *expr, FILE *out, int *count, Hashtable *hash){
    if(*count == 0){
        *count = *count + 1;
        first_math(expr, out, hash);
    }

    else{
        second_math(expr, out, hash);
    }
}

void second_math(NodeExpr *expr, FILE *out, Hashtable *hash){
    if(expr->data.binaryOp.left->type == EXPR_VARIABLE || expr->data.binaryOp.right->type == EXPR_VARIABLE){
        if(strcmp(expr->data.binaryOp.oper, "+") == 0){
            printf("plus ident\n");//TODO
        }

        else if(strcmp(expr->data.binaryOp.oper, "-") == 0){
            printf("minus ident\n");//TODO
        }

        else if(strcmp(expr->data.binaryOp.oper, "*") == 0){
            printf("multi ident\n");//TODO
        }

        else if(strcmp(expr->data.binaryOp.oper, "/") == 0){
            printf("div ident\n");//TODO
        }
    }

    else{
        if(strcmp(expr->data.binaryOp.oper, "+") == 0){
            if(expr->data.binaryOp.left->type == EXPR_INT_LITERAL){
                fprintf(out, "    add rax, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);    
            }

            else if(expr->data.binaryOp.right->type == EXPR_INT_LITERAL){
                fprintf(out, "    add rax, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
            }
        }

        else if(strcmp(expr->data.binaryOp.oper, "-") == 0){
            if(expr->data.binaryOp.left->type == EXPR_INT_LITERAL){
                fprintf(out, "    sub rax, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
            }

            else if(expr->data.binaryOp.right->type == EXPR_INT_LITERAL){
                fprintf(out, "    sub rax, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
            }
        }

        else if(strcmp(expr->data.binaryOp.oper, "*") == 0){
            if(expr->data.binaryOp.left->type == EXPR_INT_LITERAL){
                fprintf(out, "    cqo\n");
                fprintf(out, "    mov rbx, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
                fprintf(out, "    imul rbx\n");
            }

            else if(expr->data.binaryOp.right->type == EXPR_INT_LITERAL){
                fprintf(out, "    cqo\n");
                fprintf(out, "    mov rbx, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
                fprintf(out, "    imul rbx\n");
            }
        }

        else if(strcmp(expr->data.binaryOp.oper, "/") == 0){
            if(expr->data.binaryOp.left->type == EXPR_INT_LITERAL){
                fprintf(out, "    cqo\n");
                fprintf(out, "    mov rbx, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
                fprintf(out, "    idiv rbx\n");
            }

            else if(expr->data.binaryOp.right->type == EXPR_INT_LITERAL){
                fprintf(out, "    cqo\n");
                fprintf(out, "    mov rbx, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
                fprintf(out, "    idiv rbx\n");
            }
        }
    }
}

void first_math(NodeExpr *expr, FILE *out, Hashtable *hash){
    if(expr->data.binaryOp.left->type == EXPR_VARIABLE || expr->data.binaryOp.right->type == EXPR_VARIABLE){
        if(strcmp(expr->data.binaryOp.oper, "+") == 0){
            printf("plus ident\n");//TODO
        }

        else if(strcmp(expr->data.binaryOp.oper, "-") == 0){
            printf("minus ident\n");//TODO
        }

        else if(strcmp(expr->data.binaryOp.oper, "*") == 0){
            if(expr->data.binaryOp.left->type == EXPR_VARIABLE){
                int *offset = get(hash, expr->data.binaryOp.left->data.string_literal.stringValue);
                fprintf(out, "    mov rax, qword [rbp - %d]\n", (*offset - 1)*8);
            }
            else{
                fprintf(out, "    mov rax, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
            }

            if(expr->data.binaryOp.right->type == EXPR_VARIABLE){
                int *offset = get(hash, expr->data.binaryOp.right->data.string_literal.stringValue);
                fprintf(out, "    mov rbx, qword [rbp - %d]\n", (*offset - 1)*8);
            }
            else{
                fprintf(out, "    mov rbx, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
            }
            fprintf(out, "    cqo\n");
            fprintf(out, "    imul rbx\n");
        }

        else if(strcmp(expr->data.binaryOp.oper, "/") == 0){
            printf("div ident\n");//TODO
        }
    }

    else{
        if(strcmp(expr->data.binaryOp.oper, "+") == 0){
            fprintf(out, "    mov rax, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
            fprintf(out, "    add rax, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
        }

        else if(strcmp(expr->data.binaryOp.oper, "-") == 0){
            fprintf(out, "    mov rax, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
            fprintf(out, "    sub rax, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
        }

        else if(strcmp(expr->data.binaryOp.oper, "*") == 0){
            fprintf(out, "    mov rax, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
            fprintf(out, "    mov rbx, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
            fprintf(out, "    cqo\n");
            fprintf(out, "    imul rbx, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
        }

        else if(strcmp(expr->data.binaryOp.oper, "/") == 0){
            fprintf(out, "    cqo\n");
            fprintf(out, "    mov rax, %d\n", expr->data.binaryOp.left->data.int_literal.intValue);
            fprintf(out, "    mov rbx, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
            fprintf(out, "    idiv rbx, %d\n", expr->data.binaryOp.right->data.int_literal.intValue);
        }
    }
}

void var_stmnt(NodeStmnt *stmnt, FILE *out, Hashtable *hash, int *count_ints){//TODO fix these and the const ones to complete variables
    if (stmnt->type == STMNT_ASSIGNMENT){
                    
    }

    else if(stmnt->type == STMNT_DECLARATION){
        char *ident = stmnt->data.assign.ident->data.string_literal.stringValue;
        if(!contains(hash, ident)){
            int *check = malloc(sizeof(int));
            *check = 0;
            void *value = var_expr(stmnt->data.declaration.value, out, check, hash);
            fprintf(out, "    mov qword [rbp - %d],  rax\n", *count_ints * 8);
            insert(hash, ident, count_ints);
            *count_ints = *count_ints + 1;
        }

        else{
            perror("Double Assignment!\n");
        }
    }

    else if(stmnt->type == STMNT_RETURN){
        char *ret = stmnt->data.ret->data.identifier.varName;
        int *offset = get(hash, ret);
        fprintf(out, "    mov rcx, qword [rbp - %d]\n", (*offset - 1)*8);
        fprintf(out, "    call ExitProcess\n");
    }
}

void const_stmnt(NodeStmnt *stmnt, FILE *out, Hashtable *hash, int *count_ints){
    if (stmnt->type == STMNT_ASSIGNMENT){
                    
    }

    else if(stmnt->type == STMNT_DECLARATION){
        char *ident = stmnt->data.declaration.ident->data.string_literal.stringValue;
        printf("ident: %s\n", ident);
        if(!contains(hash, ident)){
            void *value = push_expr(stmnt->data.declaration.value);
            int literal = *(int*) value;
            insert(hash, ident, count_ints);
            fprintf(out, "    mov qword [rbp - %d],  %d\n", *count_ints * 8, literal);
            *count_ints = *count_ints + 1;
        }

        else{
            perror("Double Assignment!\n");
        }
    }

    else if(stmnt->type == STMNT_RETURN){
        int ret = stmnt->data.ret->data.int_literal.intValue;
        fprintf(out, "    mov rcx, qword %d\n", ret);
        fprintf(out, "    call ExitProcess\n");
    }
}

void return_last_pushed(FILE *out, int offset){
    fprintf(out, "    mov rcx, qword [rbp - %d]\n", (offset - 1)*8);
    fprintf(out, "    call ExitProcess\n");
}

void *push_expr(NodeExpr *expr){
    if(expr->type == EXPR_BINARY_OP){
        void *left_ptr = push_expr(expr->data.binaryOp.left);
        int left;
        if(left_ptr){
            left = *(int*)left_ptr;
            free(left_ptr);
        }

        else{
            left = expr->data.binaryOp.left->data.int_literal.intValue;
        }

        void *right_ptr = push_expr(expr->data.binaryOp.right);
        int right;

        if(right_ptr){
            right = *(int*)right_ptr;
            free(right_ptr);
        }

        else{
            right = expr->data.binaryOp.right->data.int_literal.intValue;
        }

        void* ptr = malloc(sizeof(int));
        int result = 0;
        if(strcmp(expr->data.binaryOp.oper, "+") == 0){//TODO checks here for all types of values e.g. write function for checking value of nodeExpr
            result = left + right;
        }

        else if(strcmp(expr->data.binaryOp.oper, "-") == 0){
            result = left - right;
        }

        else if(strcmp(expr->data.binaryOp.oper, "*") == 0){
            result = left * right;
        }

        else if(strcmp(expr->data.binaryOp.oper, "/") == 0){
            result = left / right;
        }

        memcpy(ptr, &result, sizeof(int));

        return ptr;
    }

    else if(expr->type == EXPR_INT_LITERAL){
        void* ptr = malloc(sizeof(int));
        int val = expr->data.int_literal.intValue;
        memcpy(ptr, &val, sizeof(int));
        return ptr;
    }
    return NULL;
}

void win_boiler(FILE *out){
    fprintf(out, "section .text\n");
    fprintf(out, "    global main\n");
    fprintf(out, "    extern ExitProcess\n");
    fprintf(out, "main:\n");
    
}

void win_boiler2(FILE *out){
    //If we dont do anything, return 0 automatically
    fprintf(out, "    mov rcx, 0\n");
    fprintf(out, "    call ExitProcess\n");
}

void gen_linux(FILE *out){
    fprintf(out, "section .text\n");
    fprintf(out, "    global _start\n\n");
    fprintf(out, "_start:\n");
    fprintf(out, "    mov rax, 60\n");
    fprintf(out, "    mov rdi, 0\n");
    fprintf(out, "    syscall\n");
}

int get_os(){
    #ifdef _WIN32
        return 1; // Windows
    #elif __linux__
        return 2; // Linux
    #else
        return 0; // Unknown
    #endif
}