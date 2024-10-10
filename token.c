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
    t->type = calloc(8, sizeof(char));
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