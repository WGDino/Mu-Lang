#ifndef AST_NODE_H
#define AST_NODE_H

#include "linked_list.h"
#include <stdlib.h>

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
} NodeFunction;

typedef struct NodeProgram {
    NodeFunction *main;//TODO this one needs checking since it mig´ht be better with a 
    //tree struct which I then need to build
} NodeProgram;

NodeStmnt* createStmntNodeAss(TypeKind type, NodeExpr *ident, NodeExpr *value);

NodeStmnt *createStmntNodeDec(TypeKind type, NodeExpr *ident);

NodeProgram *createProgramNode();

NodeFunction *createMainNode();

NodeExpr* createExprNode();

#endif