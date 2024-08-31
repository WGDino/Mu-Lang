#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "token_types.h"

//TODO helper klass tokenizer = token_reader
//TODO swap current setup for is_keyword and so forth.
//TODO add same checking for operators
void token_reader(char* filename, Token **tokens);

int main(int argc, char *argv[]){
    Token **tokens = calloc(20, sizeof(Token *));

    if(argc != 2 ){
        printf("Wrong Usage.\n Correct usage is muc <input.mu>\n");
    }

    else{
        printf("Lexical analysis starting\n");
        token_reader(argv[1], tokens);
    }

    for (int i = 0; i < 17; i++)
    {
        printf("Token type: %s\nToken data: %s\n\n", tokens[i]->type, tokens[i]->data);
    }
    

    return 0;
}

void token_reader(char* filename, Token **tokens){
    Token_types *tt = token_types_create();
    FILE* input = fopen(filename, "r");

    if(input != NULL){
        char buffer[25];
        int read = 0;
        int num = 0;
        int num_tokens = 0;
        Token *token;

        while (read != EOF){
            read = fgetc(input);
            if(read != ' ' && read != '(' && read != ')' && read != '\n' && read != EOF && read != ',' && read != ';' && read != '='){
                buffer[num] = read;
                num++;
            }

            else{
                if(num > 0){
                    token = token_create();
                    buffer[num] = '\0';
                    
                    if(is_keyword(tt, buffer)){
                        update_token_type(token, "Keyword", num);
                    }else{
                        update_token_type(token, "Normal", num);
                    }

                    update_token_data(token, buffer, num);
                    tokens[num_tokens] = token;
                    num_tokens++;
                    num = 0;
                }

                if(read == '(' || read == ')' || read == ',' || read == ';' || read == '='){
                    token = token_create();
                    buffer[0] = read;
                    buffer[1] = '\0';
                    update_token_type(token, buffer, num);
                    update_token_data(token, buffer, num);
                    tokens[num_tokens] = token;
                    num_tokens++;
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