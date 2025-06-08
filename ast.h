#ifndef AST_H
#define AST_H

#include "ast_node.h"
#include "token.h"
#include "linked_list.h"
#include "tokenizer.h"
#include "token_types.h"
#include <stdlib.h>
#include <stdio.h>

NodeProgram *ast_build(Linked_list *lst);

#endif