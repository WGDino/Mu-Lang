#ifndef AST_H
#define AST_H

#include "ast_node.h"
#include "token.h"
#include "linked_list.h"
#include "tokenizer.h"
#include "token_types.h"
#include <stdlib.h>

NodeProgram *ast_build();

#endif