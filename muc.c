#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"
#include "token_types.h"
#include "linked_list.h"

//TODO helper klass tokenizer = token_reader
//TODO swap current setup for is_keyword and so forth.
//TODO add same checking for operators
//TODO fix missing functions in linked_list
//TODO add types for nodes in AST
//TODO AST BUILDING
void token_reader(char* filename, Linked_list *lst);

int main(int argc, char *argv[]){
    Linked_list *lst = create_list();

    if(argc != 2 ){
        printf("Wrong Usage.\n Correct usage is muc <input.mu>\n");
    }

    else{
        printf("Lexical analysis starting\n");
        token_reader(argv[1], lst);
    }
    
    print_list(lst);

    return 0;
}

void token_reader(char* filename, Linked_list *lst){
    Token_types *tt = token_types_create();
    FILE* input = fopen(filename, "r");
    struct Node *node = get_first(lst);

    if(input != NULL){
        char buffer[25];
        int read = 0;
        int num = 0;
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
                    list_insert(token, node);
                    num = 0;
                }

                if(read == '(' || read == ')' || read == ',' || read == ';' || read == '='){//TODO handling in here similar to isKeyword
                    token = token_create();
                    buffer[0] = read;
                    buffer[1] = '\0';
                    update_token_type(token, buffer, num);
                    update_token_data(token, buffer, num);
                    list_insert(token, node);
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