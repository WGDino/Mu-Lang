#ifndef TOKEN_TYPES_H
#define TOKEN__TYPES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct token_types{
    char **keywords;
    char **operators;
} Token_types;

Token_types *token_types_create();

bool is_keyword(Token_types *tt, char *input);

bool is_operator(Token_types *tt, char *input);

void tt_remove(Token_types *tt);

#endif /* TOKEN_TYPES_H */

