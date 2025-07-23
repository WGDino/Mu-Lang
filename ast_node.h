#ifndef AST_NODE_H
#define AST_NODE_H

#include "linked_list.h"
#include <stdlib.h>
#include "token.h"
#include "arena.h"

//TODO map this to the test file and see if it works on paper
typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_POINTER,
    TYPE_ARRAY,
    TYPE_STRUCT,
    TYPE_FUNCTION, // To represent function types (return and argument types)
} TypeKind;

typedef enum {
    EXPR_INT_LITERAL,
    EXPR_FLOAT_LITERAL,
    EXPR_STRING_LITERAL,
    EXPR_CHAR_LITERAL,      // Represents a literal value like an integer, float, string, etc.
    EXPR_BINARY_OP,    // Binary operation like +, -, *, /
    EXPR_VARIABLE,     // Refers to a variable (e.g., `x`)
    EXPR_FUNCTION_CALL // Function call like `foo(1, 2)`
} ExprType;

typedef enum {
    STMNT_ASSIGNMENT,
    STMNT_DECLARATION,
    STMNT_RETURN
} StmntType;

typedef struct NodeExpr {
    ExprType type;  // Specifies the type of expression
    union {
        struct {
            int intValue;
        } int_literal;

        struct {
            float floatValue;
        } float_literal;

        struct {
            char *stringValue;
        } string_literal;

        struct {
            char charValue;
        } char_literal;

        struct {
            char *varName;   // The name of the variable (for EXPR_VARIABLE)
        } identifier;

        struct {
            char *oper;   // Binary operator (e.g., "+")
            struct NodeExpr *left;
            struct NodeExpr *right;
        } binaryOp;
    } data;
} NodeExpr;

typedef struct NodeStmnt {
    StmntType type;
    int is_const;
    union{
        struct {
            TypeKind type;
            NodeExpr *ident;
            NodeExpr *value;
        } assign;

        struct {
            TypeKind type;
            NodeExpr *ident;
            NodeExpr *value;
        } declaration;

        NodeExpr *ret;
    } data;
} NodeStmnt;

typedef struct NodeFunction{
    TypeKind returnType;
    char *name;
    Linked_list *children;
    size_t ints;
} NodeFunction;

typedef struct NodeProgram {
    NodeFunction *main;//TODO this one needs checking since it mig´ht be better with a 
    //tree struct which I then need to build
} NodeProgram;

NodeStmnt* createStmntNodeAss(TypeKind type, NodeExpr *ident, NodeExpr *value, Arena *a, int is_const);

NodeStmnt *createStmntNodeDec(TypeKind type, NodeExpr *ident, Arena *a, int is_const);

NodeStmnt* createStmntNodeRet(NodeExpr *expr, Arena *a, int is_const);

NodeProgram *createProgramNode(Linked_list *lst, Arena *a);

NodeFunction *createMainNode(Linked_list *lst, Arena *a);

NodeExpr* createExprNode(Token *token, int type, Arena *a);

NodeExpr *parse_expr(int presedence, Linked_list *lst, int offset, Arena *a, int *is_var, NodeExpr *created, FILE *out);

void print_ast(NodeFunction *root, int type);

void print_stmnt(NodeStmnt *stmtn);

void print_expr(NodeExpr *expr);

int check_presedence(char *data);
#endif