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

        while(walk != head){
            if(strcmp(walk->data_type, "func") == 0){
                //TODO fix this later
            }

            else if(strcmp(walk->data_type, "stmnt") == 0){
                NodeStmnt *stmnt = (NodeStmnt *) walk->data;
                if (stmnt->type == STMNT_ASSIGNMENT){
                    char *ident = stmnt->data.assign.ident;
                    void *value = push_expr(stmnt->data.assign.value);
                    //TODO reserve correct frame pointer for mains ints value
                    //TODO then push the values onto stack and record the identifiers in hashtable
                    //TODO return correct code
                }

                else if(stmnt->type == STMNT_DECLARATION){

                }

                else if(stmnt->type == STMNT_RETURN){

                }
                
                walk = walk->next;   
            }
        }
        win_boiler2(out);
}

void *push_expr(NodeExpr *expr){
    if(expr->type == EXPR_BINARY_OP){
        if(strcmp(expr->data.binaryOp.oper, "+") == 0){//TODO checks here for all types of values e.g. write function for checking value of nodeExpr
            int left = expr->data.binaryOp.left->data.int_literal.intValue;
            int right = expr->data.binaryOp.right->data.int_literal.intValue;
            int result = left + right;
            return &result;
        }

        else if(strcmp(expr->data.binaryOp.oper, "-") == 0){
            //TODO
        }

        else if(strcmp(expr->data.binaryOp.oper, "*") == 0){
            //TODO
        }

        else if(strcmp(expr->data.binaryOp.oper, "/") == 0){
            //TODO
        }
    }
}

void win_boiler(FILE *out){
    fprintf(out, "section .text\n");
    fprintf(out, "    global main\n");
    fprintf(out, "    extern ExitProcess\n");
    fprintf(out, "main:\n");
    
}

void win_boiler2(FILE *out){
    fprintf(out, "    sub rsp, 32\n");
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