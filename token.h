#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct token{
    char *type;
    char *data;
    bool is_keyword;
    bool is_operator;
} Token;

Token *token_create(void);

void update_token_type(Token *t, char *type, int length);

void update_token_data(Token *t, char *data, int length);

char *get_data(Token *t);

char *get_type(Token *t);

void print_token(void *data, char *type);

void set_is_operator(Token *t, bool value);

void set_is_keyword(Token *t, bool value);

bool get_is_operator(Token *t);

int tokenGetInt(Token *token);

#endif /* TOKEN_H */