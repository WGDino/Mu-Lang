#ifndef AST_NODE_H
#define AST_NODE_H

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
    EXPR_LITERAL,      // Represents a literal value like an integer, float, string, etc.
    EXPR_BINARY_OP,    // Binary operation like +, -, *, /
    EXPR_VARIABLE,     // Refers to a variable (e.g., `x`)
    EXPR_FUNCTION_CALL // Function call like `foo(1, 2)`
} ExprType;

// Struct for more complex types
typedef struct TypeNode {
    TypeKind kind;              // The kind of type (basic, pointer, array, etc.)
    struct TypeNode *subType;   // For pointers or arrays, points to the underlying type
    int arraySize;              // Array size (used if kind == TYPE_ARRAY)
    char *customTypeName;       // For custom types like structs
    struct TypeNode **paramTypes; // For function types, a list of parameter types
    int paramCount;             // Number of parameters for function types
    struct TypeNode *returnType; // Return type for functions
} TypeNode;

typedef struct ExprNode {
    ExprType type;  // Specifies the type of expression
    union {
        struct {
            int intValue;
            float floatValue;
            char *stringValue;
        } literal;           // For EXPR_LITERAL

        struct {
            char *varName;   // The name of the variable (for EXPR_VARIABLE)
        } variable;

        struct {
            char *oper;   // Binary operator (e.g., "+")
            struct ExprNode *left;
            struct ExprNode *right;
        } binaryOp;

        struct {
            char *functionName;
            struct ExprNode **arguments;
            int argumentCount;
            TypeKind returnType;
        } functionCall;
    } data;
} ExprNode;


typedef struct variableDecNode{
    char *varName;      // Name of the variable
    TypeNode *type;     // Pointer to the type node (declared type)
    struct ExprNode *initialValue; // Expression node for the initial value (can be NULL)
} VariableDecNode;

#endif