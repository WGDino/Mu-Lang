#include "token_types.h"
//TODO add peek and consume funcs

Token_types *token_types_create(){
    Token_types *tt = calloc(1, sizeof(Token_types));

    tt->keywords = calloc(8, sizeof(char *));
    tt->keywords[0] = "return";
    tt->keywords[1] = "int";
    tt->keywords[2] = "char";
    tt->keywords[3] = "if";
    tt->keywords[4] = "for";
    tt->keywords[5] = "while";
    tt->keywords[6] = "else";
    tt->keywords[7] = "void";

    tt->operators = calloc(5, sizeof(char *));
    tt->operators[0] = "+";
    tt->operators[1] = "-";
    tt->operators[2] = "*";
    tt->operators[3] = "/";
    tt->operators[4] = "=";

    return tt;
}

bool is_keyword(Token_types *tt, char *input){
    for (int i = 0; i < 8; i++)
    {
        if(!strcmp(tt->keywords[i], input)){
            return true;
        }
    }
    return false;
}

bool is_operator(Token_types *tt, char *input){
    for (int i = 0; i < 5; i++)
    {
        if(!strcmp(tt->operators[i], input)){
            return true;
        }
    }
    return false;
}

void tt_remove(Token_types *tt){
    free(tt->keywords);
    free(tt->operators);
    free(tt);
}
