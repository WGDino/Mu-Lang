#include "token.h"

Token *token_create(void){
    Token *t = malloc(sizeof(Token));
    t->type = NULL;
    t->data = NULL;
    t->is_keyword = false;
    t->is_operator = false;

    return t;
}

void update_token_type(Token *t, char *type, int length){//TODO This still needs to be more flexible later
    t->type = calloc(length, sizeof(char));
    strcpy(t->type, type);
}

void update_token_data(Token *t, char *data, int length){
    t->data = calloc(length + 1, sizeof(char));
    strcpy(t->data, data);
}

char *get_type(Token *t){
    return t->type;
}

char *get_data(Token *t){
    return t->data;
}

void set_is_keyword(Token *t, bool value){
    t->is_keyword = value;
}

void set_is_operator(Token *t, bool value){
    t->is_operator = value;
}

bool get_is_operator(Token *t){
    return t->is_operator;
}

void print_token(void *data, char *type) {
    if(strcmp(type, "token") == 0){
        Token *token = (Token *)data; // Cast void pointer to Token pointer
        if (token == NULL) {
            printf("NULL Token\n");
            return;
        }

        printf("Token:\n");
        printf("  Type: %s\n", token->type ? token->type : "NULL");
        printf("  Data: %s\n", token->data ? token->data : "NULL");
        printf("  Is Keyword: %s\n", token->is_keyword ? "true" : "false");
        printf("  Is Operator: %s\n", token->is_operator ? "true" : "false");
    }

    else{
        printf("Type error!\nTrying to print non-token with print_token.\n");
    }
}

int tokenGetInt(Token *token){
    int i = 0;
    int num = 0;
    while(token->data[i] != '\0'){
        num = num * 10 + (token->data[i] - 48);
        i++;
    }
    return num;
}