typedef enum { typeCon, typeId, typeOpr } nodeEnum;

/* constantes */
typedef struct {
    int value;   /* valor da constante */
} conNodeType;

/* identificadores */
typedef struct {
    int i;       /* índice para o array de símbolos */
} idNodeType;

/* operadores */
typedef struct {
    int oper;   /* operador */
    int nops;   /* quantidade de operandos */
    struct nodeTypeTag **op;  /* operandos */
} oprNodeType;

typedef struct nodeTypeTag {
    nodeEnum type;   /* tipo do nó */
    union {
        conNodeType con;   /* constantes */
        idNodeType id;     /* identificadores */
        oprNodeType opr;   /* operadores */
    };
} nodeType;

extern int sym[26];