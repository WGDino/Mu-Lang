#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token_types.h"
#include "linked_list.h"

void token_reader(char* filename, Linked_list *lst, Token_types *tt);

bool is_alpha_num(int check);

bool is_FloatLit(char *str, int length);

bool is_IntLit(char *str, int length);

#endif /* TOKENIZER_H */