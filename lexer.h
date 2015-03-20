#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*
Submitted By:
		Team - 24	 Group - 1
	Prateek Jain	2012C6PS392P
	Vishal Goyal	2012A7PS071P
*/
#define hashSize 16
#define MAXSIZE 500
struct vector{
	float x;
	float y;
};

struct linear{
	struct vector *start;
	struct vector *end;
	float frict;
};

struct object{
	struct vector *vel;
	struct vector *acc;
	struct vector *pos;
	float mass;
};

struct tokenNode{
	char *token;
	char *value;
	struct tokenNode *next;
};

struct lineNode{
	int no;
	struct tokenNode *tokenList;
	struct lineNode *next;
};

union genType{
	int i;
	float f;
	struct linear *lin;
	struct object *obj;
	struct vector *vec; 
};
struct lineNo{
	int lineno;
	struct lineNo *next;
};
struct idNode{
	char name[255];
	char *type;
	char funcName[255];
	struct lineNo *lineno;
	int scope;
	union genType *val;
	struct idNode *next;
};
struct stack
{
    struct parseNode *stk[MAXSIZE];
    int top;
};
typedef struct stack STACK;
struct stack1
{
    struct xnode *stk[MAXSIZE];
    int top;
};
typedef struct stack1 STACK1;
struct queue
{
    struct parseNode *q[MAXSIZE];
    int top;
	int entry;
};
typedef struct queue QUEUE;


//parser ends

char idCalVal[6];
static char *tokens[54] = {"ACC", "ADD", "AND", "ASSIGN", "AT", "COM", "COMMA", "DIV", "DOT", "EC", "EP", "FE", "FLOAT", "FLOATCONST", "FRICT", "FS", "GT", "GTE", "ID","INF", "ININ", "INIT", "INT", "INTCONST", "LC", "LIN", "LNR", "LOOP", "LP", "LS", "LT", "LTE", "MAS", "MUL", "NOT", "OBJECT", "OR", "OUT","OUTA", "POS", "RC", "RETURN", "RP", "RS", "SEP", "SMC", "SP", "SUB", "TIME", "VECTOR", "VEL", "WHEN", "XP", "YP"};


//parser


struct node{
char a[20];
struct node* parent;
struct node* down;
struct node* next;
};


struct parseNode{
char name[20];
char val[255];
int lineno;
struct parseNode *parent;
struct parseNode *down;	
struct parseNode *next;
};

struct xnode{
struct node *c1;
struct parseNode *c2;
};


char getChar(FILE *fp);
int getSize(struct lineNode *list);
void getArray(char *arr[],struct lineNode *list);
int noLength(int no);
void saveLexer(struct lineNode *list,char *name);
struct lineNode *lexer(FILE *fp,struct lineNode *list,struct idNode *hashTable[],struct idNode *hashTable1[],struct idNode *hashTable2[]);
struct lineNode *getNode(int lineno,struct lineNode *list);
void fillDataType(struct lineNode *list,struct idNode *hashTable[]);
void decFilePoint(FILE *fp);


//parser
struct node *Parser(char *t[],int size);
void backToRoot(int i);
void traverse(struct node* start,int tab);
void hashNames(struct parseNode *tree,struct idNode *SymbolTable[]);
void printHash(struct idNode *SymbolTable[]);
void fillNames(struct parseNode *parseTree,struct idNode *hashTable[],struct idNode *hashTable1[],struct idNode *hashTable2[]);
int getNumber(char *a);
struct parseNode *ReduceExpr(struct parseNode *root);
void traverse1(struct parseNode* start,int tab,int c);
struct parseNode *convertParse(struct node *root);
int h(char *x,int len);

void abc(struct parseNode *t);
void recCreateST(struct parseNode *tree,struct idNode *ST[],struct lineNode *list,char *fname);
struct idNode *createST(struct parseNode *tree,struct idNode *ST[],struct lineNode *list);
void fillType(struct parseNode *tree,struct idNode *symbolTable[],struct lineNode *list);
