#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast_node.h"
#include "hashtable.h"

void gen_code(NodeProgram *prog);

void gen_linux(FILE *out);

void gen_windows(FILE *out, NodeProgram *prog);

int get_os();

void run_windows();

void win_boiler(FILE *out);

void *push_expr(NodeExpr *expr);

void win_boiler2(FILE *out);

void return_last_pushed(FILE *out, int offset);

void const_stmnt(NodeStmnt *stmnt, FILE *out, Hashtable *hash, int *count_ints, bool is_main);

void var_stmnt(NodeStmnt *stmnt, FILE *out, Hashtable *hash, int *count_ints, bool is_main);

void *var_expr(NodeExpr *expr, FILE *out, int *count, Hashtable *hash);

void var_expr_math(NodeExpr *expr, FILE *out, int *count, Hashtable *hash);

void first_math(NodeExpr *expr, FILE *out, Hashtable *hash);

void second_math(NodeExpr *expr, FILE *out, Hashtable *hash);

void gen_function(FILE *out, NodeFunction *func, bool is_main, Hashtable *hash);
#endif