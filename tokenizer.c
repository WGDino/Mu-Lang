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

                    else if(is_IntLit(buffer, num)){
                        update_token_type(token, "Int_Lit", num);
                    }

                    else if(is_FloatLit(buffer, num)){
                        update_token_type(token, "Float_Lit", num);
                    }   
                    
                    else{
                        update_token_type(token, "Identifier", num);
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

bool is_IntLit(char *str, int length){
    bool check = true;

    for (int i = 0; i < length; i++){
        if((str[i] < 48 || str[i] > 57)){
            check = false;   
        }
    }
    return check;
}

bool is_FloatLit(char *str, int length){
    bool check = true;
    int point_cnt = 0;

    for (int i = 0; i < length; i++){
        if((str[i] < 48 || str[i] > 57)){
            if(str[i] != '.' || (str[i] == '.' && point_cnt > 0)){
                check = false;
            }
        }
        if(str[i] == '.'){
            point_cnt++;
        }
    }
    return check;
}