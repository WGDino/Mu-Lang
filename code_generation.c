#include "code_generation.h"

void gen_code(NodeProgram *prog){
    FILE *out = fopen("muc_out.asm", "w");

    if(get_os() == 1){//Windows
        gen_windows(out);
        run_windows();
        fclose(out);
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
    int result = system("nasm -f win64 muc_out.asm -o muc_out.o");

    if(result != 0){
        perror("Nasm failed!\n");
    }

    result = system("ld -e _start -o muc_out.exe muc_out.o -lkernel32");

    if(result != 0){
        perror("GCC failed!\n");
    }

}

void gen_windows(FILE *out){
    fprintf(out, "section .text\n");
    fprintf(out, "    global _start\n");
    fprintf(out, "    extern ExitProcess\n\n");
    fprintf(out, "_start:\n");
    fprintf(out, "    sub rsp, 32\n");
    fprintf(out, "    mov rcx, 1\n");
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