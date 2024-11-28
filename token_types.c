#include "token_types.h"

Token_types *token_types_create(){
    Token_types *tt = calloc(1, sizeof(Token_types));

    tt->keywords = calloc(6, sizeof(char *));
    tt->keywords[0] = "return";
    tt->keywords[1] = "if";
    tt->keywords[2] = "for";
    tt->keywords[3] = "while";
    tt->keywords[4] = "else";
    tt->keywords[5] = "void";

    tt->operators = calloc(5, sizeof(char *));
    tt->operators[0] = "+";
    tt->operators[1] = "-";
    tt->operators[2] = "*";
    tt->operators[3] = "/";
    tt->operators[4] = "=";

    tt->types = calloc(4, sizeof(char *));
    tt->types[0] = "int";
    tt->types[1] = "float";
    tt->types[2] = "char";
    tt->types[3] = "string";

    return tt;
}

bool is_type(Token_types *tt, char *input){
    for (int i = 0; i < 4; i++){
        if(!strcmp(tt->types[i], input)){
            return true;
        }
    }
    return false;
}

bool is_keyword(Token_types *tt, char *input){
    for (int i = 0; i < 6; i++){
        if(!strcmp(tt->keywords[i], input)){
            return true;
        }
    }
    return false;
}

bool is_operator(Token_types *tt, char *input){
    for (int i = 0; i < 5; i++){
        if(!strcmp(tt->operators[i], input)){
            return true;
        }
    }
    return false;
}

void tt_remove(Token_types *tt){
    free(tt->keywords);
    free(tt->operators);
    free(tt->types);
    free(tt);
}
