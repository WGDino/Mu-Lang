#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

//TODO helper class for allocating array for tokens
//TODO helper klass tokenizer = token_reader
//TODO mbe add another argument to token with cntext of what the token is like function, argument etc
Token* token_reader(char* filename);

int main(int argc, char *argv[]){
    if(argc != 2 ){
        printf("Wrong Usage.\n Correct usage is muc <input.mu>");
    }

    else{
        printf("Lexical analysis starting\n");
        token_reader(argv[1]);
    }

    return 0;
}

Token* token_reader(char* filename){
    FILE* input = fopen(filename, "r");

    if(input != NULL){
        char buffer[25];
        int read = 0;
        int num = 0;

        while (read != EOF){
            read = fgetc(input);
            if(read != ' ' && read != '(' && read != ')' && read != '\n' && read != EOF && read != ',' && read != ';'){
                buffer[num] = read;
                num++;
            }

            else{
                if(num > 0){
                    buffer[num] = '\0';
                    printf("%s\n", buffer);
                    num = 0;
                }

                if(read == '(' || read == ')' || read == ',' || read == ';'){
                    buffer[0] = read;
                    buffer[1] = '\0';
                    printf("%s\n", buffer);
                    num = 0;
                }
            }
        }
        
        fclose(input);
    }

    else{
        printf("Could not open file");
        fclose(input);
    }
}