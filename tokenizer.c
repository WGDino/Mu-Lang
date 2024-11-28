#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token.h"

void token_reader(char* filename, Linked_list *lst, Token_types *tt){
    FILE* input = fopen(filename, "r");
    struct Node *node = get_first(lst);

    if(input != NULL){
        char buffer[25];
        int read = 0;
        int num = 0;
        Token *token;

        while (read != EOF){
            read = fgetc(input);
            if(is_alpha_num(read)){
                buffer[num] = read;
                num++;
            }

            else{
                if(num > 0){
                    token = token_create();
                    buffer[num] = '\0';
                    
                    if(is_keyword(tt, buffer)){
                        update_token_type(token, "Keyword", num);
                    }

                    else if(is_type(tt, buffer)){
                        update_token_type(token, "Type", num);
                    }
                    
                    else{
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
                    num = 2;
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

bool is_alpha_num(int check){
    if(check >= 48 && check <= 57){
        return true;
    }

    else if(check >= 65 && check <= 90){
        return true;
    }

    else if(check >= 97 && check <= 122){
        return true;
    }

    return false;
}