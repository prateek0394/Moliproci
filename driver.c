#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "lexer.h"

/*
Submitted By:
	Team - 24 	Group - 1	
	Prateek Jain	2012C6PS392P
	Vishal Goyal	2012A7PS071P
*/
int main(int argc, char *argv[]){
if(argc!=2){
exit(0);
}	
FILE *fp;
fp = fopen(argv[1],"r+");
struct idNode *hashTable[hashSize] = {NULL};
struct idNode *hashTable1[hashSize] = {NULL};
struct idNode *hashTable2[hashSize] = {NULL};
struct idNode *listPoint;
struct lineNode *list;
list = lexer(fp,list,hashTable,hashTable1,hashTable2);
if(list==NULL)
exit(0);
printf("\n\n\t\t***********Lexer Tokens(line wise)***********\n\n");
saveLexer(list,argv[1]);
int size = getSize(list);
char *t[size];
getArray(t,list);
fclose(fp);
int i;
struct node *start = Parser(t,size);
//printf("***********Parse Tree***********\n");
//traverse(start,0);
struct parseNode *parseTree = convertParse(start);
struct parseNode *x;
x = ReduceExpr(parseTree);
fillNames(parseTree,hashTable,hashTable1,hashTable2);
printf("\n\n\t\t***********Abstract Syntax Tree***********\n\n");
traverse1(x,0,0);
struct idNode *ST[hashSize] = {NULL};
char fname[256];
memset(fname,'\0',256);
recCreateST(parseTree,ST,list,fname);
printf("\n\n\t\t***********Symbol Table***********\n\n");
printHash(ST);
return 0;
}
