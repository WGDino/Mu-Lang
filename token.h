#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct token{
    char *type;
    char *data;
} Token;

Token *token_create(void);

void update_token_type(Token *t, char *type, int length);

void update_token_data(Token *t, char *data, int length);

#endif /* TOKEN_H */