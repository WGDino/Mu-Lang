#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "token_types.h"
#include "linked_list.h"

void token_reader(char* filename, Linked_list *lst, Token_types *tt);

#endif /* TOKENIZER_H */