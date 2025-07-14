#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast_node.h"

void gen_code(NodeProgram *prog);

void gen_linux(FILE *out);

void gen_windows(FILE *out);

int get_os();

void run_windows();

#endif