#ifndef AST_NODE_H
#define AST_NODE_H

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

typedef struct ExprNode{
    
} ExprNode;

typedef struct variableDecNode{
    char *varName;      // Name of the variable
    TypeNode *type;     // Pointer to the type node (declared type)
    struct ExprNode *initialValue; // Expression node for the initial value (can be NULL)
} VariableDecNode;

#endif