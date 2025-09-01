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

void *const_expr(NodeExpr *expr, FILE *out){
    if(expr->type == EXPR_BINARY_OP){
        //TODO figure this shit out l8r
    }
}

void var_stmnt(NodeStmnt *stmnt, FILE *out, Hashtable *hash, int *count_ints){//TODO fix these and the const ones to complete variables
    if (stmnt->type == STMNT_ASSIGNMENT){
                    
    }

    else if(stmnt->type == STMNT_DECLARATION){
        char *ident = stmnt->data.assign.ident->data.string_literal.stringValue;
        if(!contains(hash, ident)){
            printf("Variable statement!\n");
            //TODO here we want to do asm math
            void *ptr = const_expr(stmnt->data.declaration.value, out);
            //TODO we need to figure out the order of things but the general idea is:
            //TODO we have the inner-most expr in one register and the outer most in another
            //TODO find the inner most by doing recusively if(node.type != int) call the function again
            //TODO if both left and right is int - put them in registers and do the corect operation
            //TODO then keep straight which registers are used for the right and left side and we should be good
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
        char *ident = stmnt->data.assign.ident->data.string_literal.stringValue;
        if(!contains(hash, ident)){
            void *value = push_expr(stmnt->data.assign.value);
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