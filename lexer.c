#include "lexer.h"
/*
Submitted By:
	Team - 24 	Group - 1
	Prateek Jain	2012C6PS392P
	Vishal Goyal	2012A7PS071P
*/
char getChar(FILE *fp){
char c=fgetc(fp);
return c;
}

int getSize(struct lineNode *list){
struct lineNode *list1;
struct tokenNode *trav;
int size=0;
for(list1=list;list1!=NULL;list1=list1->next){
for(trav = list1->tokenList;trav!=NULL;trav=trav->next){
size++;
}}
return size;
}

void getArray(char *arr[],struct lineNode *list){
struct lineNode *list1;
struct tokenNode *trav;
int size=0;
int k=0;
int intno = 0;
int floatno = 0;
char buff[8];
char b[4];
for(list1=list;list1!=NULL;list1=list1->next){
for(trav = list1->tokenList;trav!=NULL;trav=trav->next){
if(strcmp("ID",trav->token)==0){
arr[size] = (char *)malloc(7);
memset(arr[size],'\0',sizeof(arr[size]));
memset(b,'\0',sizeof(b));
sprintf(b,"%d",k);
strcat(arr[size],"ID");
strcat(arr[size],b);
size++;
k++;
}
else if(strcmp("INTCONST",trav->token)==0){
arr[size] = (char *)malloc(11);
memset(arr[size],'\0',sizeof(arr[size]));
memset(b,'\0',sizeof(b));
sprintf(b,"%d",intno);
strcat(arr[size],"INTCONST");
strcat(arr[size],b);
size++;
intno++;
}else if(strcmp("FLOATCONST",trav->token)==0){
arr[size] = (char *)malloc(13);
memset(arr[size],'\0',sizeof(arr[size]));
memset(b,'\0',sizeof(b));
sprintf(b,"%d",floatno);
strcat(arr[size],"FLOATCONST");
strcat(arr[size],b);
size++;
floatno++;
}
else{
arr[size++] = trav->token;
}
}
}
}

void decFilePoint(FILE *fp){
fseek(fp,-1*sizeof(char),SEEK_CUR);
}

int noLength(int no){
	int x = 1;
	while(no/10!=0){
	x++;
	no = no/10;
}
return x;
}

void saveLexer(struct lineNode *list,char *name){
char buff[250];
memset(buff,'\0',250);
strcat(buff,"LexerResultFor");
strcat(buff,name);
FILE *fp1 = fopen(buff,"w+");
struct lineNode *list1;
struct tokenNode *trav;
list1 = list;
int idT=0;
int idI=0;int idF=0;
for(list1=list;list1!=NULL;list1=list1->next){
	for(trav = list1->tokenList;trav->next!=NULL;trav=trav->next){
		if(strcmp(trav->token,"ID")==0){
			fprintf(fp1,"\"%s%d\",",trav->token,idT);
			printf("\"%s%d\",",trav->token,idT);
			idT++;
		}
		else if(strcmp(trav->token,"INTCONST")==0){
			fprintf(fp1,"\"%s%d\",",trav->token,idI);
			printf("\"%s%d\",",trav->token,idI);
			idI++;
		}
		else if(strcmp(trav->token,"FLOATCONST")==0){
			fprintf(fp1,"\"%s%d\",",trav->token,idF);
			printf("\"%s%d\",",trav->token,idF);
			idF++;
		}
		else{
			fprintf(fp1,"\"%s\",",trav->token);
			printf("\"%s\",",trav->token);
		}
	}
	fprintf(fp1,"\"%s\"\n",trav->token);
	printf("\"%s\"\n",trav->token);
}
fclose(fp1);
}


struct lineNode *lexer(FILE *fp,struct lineNode *list,struct idNode *hashTable[],struct idNode *hashTable1[],struct idNode *hashTable2[]){
char c;
int tokenID = -1;
int IDno = 0;
int intno = 0;
int floatno = 0;
struct lineNode *LN; 
int lineno = 0;
list = (struct lineNode *)malloc(sizeof(struct lineNode));
struct tokenNode *TN;
TN = (struct tokenNode *)malloc(sizeof(struct tokenNode));
list->no = lineno;
list->tokenList = TN;
LN = list; 
int state = 0;
char ex;
while((c=getChar(fp)) && c!=EOF){
switch(state){
case -4:
{	int st = 0;
	fseek(fp,-2*sizeof(char),SEEK_CUR);
	ex = getChar(fp);
	while(ex!=' ' && ex!='<' && ex!='>' && ex!='(' && ex!=')' && ex!='{' && ex!='}' && ex!='=' && ex!='['&& ex!=']' && ex!='+' && ex!='-' && ex!='*' && ex!='/' && ex!=',' && ex!=';' && ex!='\n'){
	fseek(fp,-2*sizeof(char),SEEK_CUR);
	ex = getChar(fp);
}
	char buff[255];
	while((ex=getChar(fp)) && ex!=' ' && ex!='<' && ex!='>' && ex!='(' && ex!=')' && ex!='{' && ex!='}' && ex!='=' && ex!='['&& ex!=']' && ex!='+' && ex!='-' && ex!='*' && ex!='/' && ex!=',' && ex!=';' && ex!='\n'){
	if(st>=255){
	printf("**************************ERROR********************variable limit exceeded\n");
	return NULL;
}
	buff[st++] = ex;
	}
	int index = IDno%(hashSize-1);
	IDno++;
	struct idNode *trav;
	if(hashTable[index]==NULL){
	hashTable[index] = (struct idNode *)malloc(sizeof(struct idNode));
	trav = hashTable[index];
}else{
	trav = hashTable[index];
	while(trav->next!=NULL){
	trav = trav->next;
}
	trav->next= (struct idNode *)malloc(sizeof(struct idNode));
	trav=trav->next;
}
	memset(trav->name, '\0',sizeof(trav->name));
	strncpy(trav->name,buff,st);
	trav->lineno = (struct lineNo *)malloc(sizeof(struct lineNo));
	trav->lineno->lineno = lineno+1;
	decFilePoint(fp);
	TN->token = tokens[18];
	TN->value = (char *)malloc(st+1);
	memset(TN->value,'\0',st+1);
	strncpy(TN->value,buff,st);
	state = -2;
	break;
}
case -3:
	LN->next = (struct lineNode *)malloc(sizeof(struct lineNode));
	LN = LN->next;
	LN->no = ++lineno;
	TN = (struct tokenNode *)malloc(sizeof(struct tokenNode));
	LN->tokenList = TN;
	state = 0;
	decFilePoint(fp);
	break;
case -2:
	TN->next =  (struct tokenNode *)malloc(sizeof(struct tokenNode));
	TN=TN->next;
	state = 0;
	decFilePoint(fp);
	break;
case -1:
	printf("****************ERROR****************\n in line number :%d\n",lineno+1);
	return NULL;	
case 0:
	tokenID = -1;
	if (c=='_'){state = 1;break;}
	else if (c=='='){ state = 2;break;}
	else if (c=='+'){
	TN->token = tokens[1];
	state = -2;
	break;
}
	else if (c=='-'){
	TN->token = tokens[47];
	state = -2;
	break;
}
	else if (c=='*'){
	TN->token = tokens[33];
	state = -2;
	break;
}
	else if (c=='/'){
	TN->token = tokens[7];
	state = -2;
	break;
}
	else if (c==','){
	TN->token = tokens[6];
	state = -2;
	break;
}
	else if (c==';'){
	TN->token = tokens[45];
	state = -2;
	break;
}
	else if (c==')'){
	TN->token = tokens[42];
	state = -2;
	break;
}
	else if (c=='('){
	TN->token = tokens[28];
	state = -2;
	break;
}
	else if (c=='}'){
	TN->token = tokens[40];
	state = -2;
	break;
}
	else if (c=='{'){
	TN->token = tokens[24];
	state = -2;
	break;
}
	else if (c==']'){
	TN->token = tokens[43];
	state = -2;
	break;
}
	else if (c=='['){
	TN->token = tokens[29];
	state = -2;
	break;
}
	else if (c=='.'){
	TN->token = tokens[8];
	state = -2;
	break;
}
	else if (c=='<'){
	state = 3;
	break;
}
	else if (c=='>'){
	state = 4;
	break;
}
	else if (c=='!'){
	if(getChar(fp)=='!'){
	TN->token = tokens[5];
	while(getChar(fp)!='\n'){}
	decFilePoint(fp);
	state = 0;	
	break;
}else{
	state = -1;
	break;
}
}
	else if (c=='a'){
	state = 5;
break;
}
	else if (c=='e'){
	if(getChar(fp)=='n' && getChar(fp)=='d'){
	tokenID = 10;
	state = 9;
	break;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state = -4;
	break;
}
}
	else if (c=='f'){
	state = 10;
	break;
}
	else if (c=='i'){
	if(getChar(fp)=='n'){
	state = 17;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state = -4;
}
break;
}else if (c=='l'){
	state = 11;
	break;
}
	else if (c=='m'){
if(getChar(fp)=='a' && getChar(fp)=='s' && getChar(fp)=='s'){
	tokenID = 32;
	state = 7;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state = -4;
}
break;
}
	else if (c=='n'){
if(getChar(fp)=='o' && getChar(fp)=='t'){
	tokenID = 34;
	state = 7;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state = -4;
}
break;
}
	else if (c=='o'){
	state = 13;
	break;
}
	else if (c=='p'){
	decFilePoint(fp);	
	tokenID = 39;
	state = 9;
	break;
}
	else if (c=='r'){
if(getChar(fp)=='e' && getChar(fp)=='t' && getChar(fp)=='u' && getChar(fp)=='r' && getChar(fp)=='n'){
	tokenID = 41;
	state = 7;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state = -4;
}
break;

}
	else if (c=='s'){
	if(getChar(fp)=='t' && getChar(fp)=='a' && getChar(fp)=='r' && getChar(fp)=='t'){
	tokenID = 46;
	state = 9;
	break;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state =-4;
	break;
}
}
	else if (c=='t'){
	char f =getChar(fp); 
	if(f==' ' || f == '=' || f=='>' || f=='<'|| f=='+' ||f=='-' ||f=='*'||f=='/'||f==','||f==';'||f==')'||f=='}'||f==']'){
	decFilePoint(fp);
	TN->token = tokens[48];
	state = -2;
}else{
	decFilePoint(fp);
	state = -4;
}
	break;
}
	else if (c=='v'){
	state = 15;
	break;
}
	else if (c=='w'){
	char t;
	if(getChar(fp)=='h' && getChar(fp)=='e' && getChar(fp)=='n' && ((t =getChar(fp)) && (t =='(' || t ==' '))){
decFilePoint(fp);
TN->token = tokens[51];
	state = -2;
}else{
	decFilePoint(fp);
	tokenID =-1 ;
	state = -4;
}
break;
}
	else if (c=='x'){
	tokenID = 52;
	state = 9;
	break;
}
	else if (c=='y'){
	tokenID = 53;
	state = 9;
	break;
}
	else if (c<='9' && c>='0'){
	tokenID = 23;
	char n = c;
	int odot = 0;
	int count = 0,b = 0;
	char buff[255];
	memset(buff,'\0',255);
	while(1){
	if(((n>'9'|| n<'0') && n!='.') || odot>1){
	decFilePoint(fp);
	break;
}
	if(odot>=1)
		b++;
	if(n=='.'){
	tokenID = 13;
	odot++;
}
	buff[count++] = n;
	n = getChar(fp);
}
	if((n>='a' && n<='z') || (n>='A' && n<='Z'))
	state = -1;
	else if(odot>1 ||(odot==1 && b==0) ){
	state = -1;
}else{
	struct idNode *trav;
	int index = 0;	
	if(odot==1){
		index = floatno%(hashSize-1);
	floatno++;
if(hashTable2[index]==NULL){
	hashTable2[index] = (struct idNode *)malloc(sizeof(struct idNode));
	trav = hashTable2[index];
}else{
	trav = hashTable2[index];
	while(trav->next!=NULL){
	trav = trav->next;
}
	trav->next= (struct idNode *)malloc(sizeof(struct idNode));
	trav=trav->next;
}
}else{
	index = intno%(hashSize-1);
	intno++;
	if(hashTable1[index]==NULL){
	hashTable1[index] = (struct idNode *)malloc(sizeof(struct idNode));
	trav = hashTable1[index];
}else{
	trav = hashTable1[index];
	while(trav->next!=NULL){
	trav = trav->next;
}
	trav->next= (struct idNode *)malloc(sizeof(struct idNode));
	trav=trav->next;
}
}
	memset(trav->name, '\0',sizeof(trav->name));
	strcpy(trav->name,buff);
	trav->lineno = (struct lineNo *)malloc(sizeof(struct lineNo));
	trav->lineno->lineno = lineno+1;
	TN->token = tokens[tokenID];
	state = -2;
}
	break;
}else if (c=='\n'){
	TN->token = tokens[44];
	state = -3;
	break;
}
	else if (c==' '){ 
state = 0;
break;
}
	else if((c >='a' && c<='z') || (c >= 'A' && c<='Z')){
	state = -4;
	decFilePoint(fp);
	break;
}else{
	state = -1;
	break;
}
break;
//case 0 ends
case 1:
	if(c=='i'){
	if(getChar(fp)=='n' && getChar(fp)=='i' && getChar(fp)=='t' && getChar(fp)=='_'){
	char t = getChar(fp);
	if(!(t=='(' ||t==' ')){
	state = -1;
	break;
}else{
	decFilePoint(fp);
	TN->token = tokens[21];
	state = -2;
	break;
	}
}else{state = -1;
	break;
}
}else{state = -1;
	break;	
}
//case 1 ends
case 2:
	if(c=='='){
	TN->token = tokens[9];
	state = -2;
	break;
	}
	else if(c=='>'){
	TN->token = tokens[3];
	state = -2;
	break;		
}
	else{
	state = -1;
	break;	
	}
//case 2 ends
case 3:
	if(c=='<'){
	TN->token = tokens[15];
	state = -2;
	break;
	}
	else if(c=='='){
	TN->token = tokens[31];
	state = -2;
	break;
}
	else{
	TN->token = tokens[30];
	state = -2;
	decFilePoint(fp);
	break;
}
//case 3 ends
case 4:
	if(c=='>'){
	TN->token = tokens[11];
	state = -2;
	break;
}
	else if(c=='='){
	TN->token = tokens[17];
	state = -2;
	break;
}
	else{
	TN->token = tokens[16];
	state = -2;
	decFilePoint(fp);
	break;
}
//case 4 ends
case 5:
	if(c=='n'){
	tokenID = 2;
	state = 6;
	break;
//and
}else if(c=='t'){
	tokenID = 4;
	state = 7;
	break;
}else if(c=='c'){
	tokenID = 0;
	state = 8;
	break;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state = -4;
	break;
}
//case 5 ends
case 6:
	if(c=='d'){
	state = 7;
	break;
}else{
decFilePoint(fp);
tokenID = -1;
	state = -4;
	break;
}
//case 6 ends
case 7:
	if(c==' ' || c=='\n'){
	if(tokenID>=0){
	TN->token = tokens[tokenID];
	state = -2;
	break;
}else{
	decFilePoint(fp);
	state = -4;
	break;
}
}else{
	decFilePoint(fp);
	state = -4;
	break;
}
//case 7 ends
case 8:
	if(c=='c'){
	state = 7;
	break;
}else{
decFilePoint(fp);
	state = -4;
	break;
}
//case 8 ends
case 9:
	if(c=='p' && getChar(fp)=='o' && getChar(fp)=='s'){
	state = 7;
	break;
}else{
	decFilePoint(fp);
	tokenID = -1;
	state = -4;
	break;
}
//case 9 ends
case 10:
if(c=='r' && getChar(fp)=='i'  && getChar(fp)=='c'  && getChar(fp)=='t'){
tokenID = 14;
state = 7;
}else if(c =='l' && getChar(fp)=='o'){
state = 19;
}else{
decFilePoint(fp);
state = -4;
tokenID = -1;
}
break;
//case 10 ends
case 11:
if(c=='i' && getChar(fp)=='n'){
	state = 12;
}else if(c=='o' && getChar(fp)=='o' && getChar(fp)=='p'){
tokenID = 27;
state = 7;
}else{
decFilePoint(fp);
tokenID = -1;
state = -4;
}
break;
//case 11 ends
case 12:
if(c==' '){
tokenID = 25;
decFilePoint(fp);
state = 7;
}else if(c=='e' && getChar(fp)=='a' && getChar(fp)=='r'){
tokenID = 26;
state = 7;
}else{
decFilePoint(fp);
tokenID = -1;
state = -4;
}
break;
//case 12 ends
case 13:
if(c=='r'){
tokenID=36;
state = 7;
}else if(c=='b' && getChar(fp)=='j' && getChar(fp)=='e' && getChar(fp)=='c' && getChar(fp)=='t'){
tokenID=35;
state = 7;
}
else if(c=='u' && getChar(fp)=='t'){
state = 14;
}
else{
decFilePoint(fp);
tokenID=-1;
state = -4;
}
break;
//case 13 ends
case 14:
if(c=='(' || c==' '){
decFilePoint(fp);
TN->token = tokens[37];
state = -2;
}else if(c=='_' && getChar(fp)=='a' && getChar(fp)=='l' && getChar(fp)=='l'){
char t = getChar(fp);
if(t=='(' || t==' '){
decFilePoint(fp);
TN->token = tokens[38];
state = -2;
}
}else{
	decFilePoint(fp);
tokenID = -1;
state = -4;
}
break;
//case 14 ends
case 15:
if(c=='e'){
state = 16;
}else{
decFilePoint(fp);
tokenID = -1;
state = -4;
}
break;
//case 15 ends
case 16:
if(c=='c' && getChar(fp)=='t' && getChar(fp)=='o' && getChar(fp)=='r'){
tokenID = 49;
state = 7;
}else if( c=='l'){
tokenID = 50;
state = 7;
}else{
	decFilePoint(fp);
tokenID = -1;
state = -4;
}
break;
//case 16 ends
case 17:
if(c=='_'){
tokenID = 20;
decFilePoint(fp);
state = 18;
}else if(c=='t'){
tokenID=22;
state = 7;
}else{
decFilePoint(fp);
tokenID = -1;
state = -4;
}
break;
//case 17 ends
case 18:
if(c=='_'  && getChar(fp)=='i' && getChar(fp)=='n' && getChar(fp)=='p'){
char df = getChar(fp);
if(df =='('|| df ==' '){
decFilePoint(fp);
TN->token = tokens[tokenID];
state = -2;
}else{
state = -1;
}
tokenID = -1;
}else{
decFilePoint(fp);
tokenID = -1;
state = -4;
}
break;
//case 18 ends
case 19:
if(c=='a' && getChar(fp)=='t'){
state = 7;
tokenID = 12;
}
else if(c=='_'){
decFilePoint(fp);
state = 18;
tokenID = 19;
}else{
decFilePoint(fp);
state = -4;
tokenID = -1;
}
break;
//case 19 ends
}//switch ends

}//while ends
return list;
}

struct lineNode *getNode(int lineno,struct lineNode *list){
struct lineNode *l;
for(l=list;l->no!=lineno;l=l->next){
}
return l;
}

void fillDataType(struct lineNode *list,struct idNode *hashTable[]){

struct idNode *k;
struct lineNode *l = list;
struct tokenNode *l1;
int i;
for(i=0;i<hashSize;i++){
if(hashTable[i]!=NULL){
for(k=hashTable[i];k!=NULL;k=k->next){
l = getNode(k->lineno->lineno-1,list);
l1 = l->tokenList;
if(strcmp("OBJECT",l1->token)==0 || strcmp("LNR",l1->token)==0 || strcmp("INT",l1->token)==0 || strcmp("FLOAT",l1->token)==0 || strcmp("VECTOR",l1->token)==0){
	k->type = l1->token;
}
}
}
}
}

/*int main( int argc, char *argv[] ){
if(argc!=2){
exit(0);
}	
FILE *fp;
char buff[250];
memset(buff,'\0',250);
strcat(buff,"LexerResultFor");
strcat(buff,argv[1]);
FILE *fp1 = fopen(buff,"w+");
fp = fopen(argv[1],"r+");
struct idNode *hashTable[hashSize] = {NULL};
//struct idNode *idList = (struct idNode *)malloc(sizeof(struct idNode));
struct idNode *listPoint;
struct lineNode *list;
list = lexer(fp,list,hashTable);
//fillDataType(list,hashTable);
struct lineNode *list1;
struct tokenNode *trav;
list1 = list;
int idT=0;
int idI=0;int idF=0;
for(list1=list;list1!=NULL;list1=list1->next){
//printf("%d\t",list1->no);
for(trav = list1->tokenList;trav->next!=NULL;trav=trav->next){
if(strcmp(trav->token,"ID")==0){
fprintf(fp1,"\"%s%d\",",trav->token,idT);
idT++;
}
else if(strcmp(trav->token,"INTCONST")==0){
fprintf(fp1,"\"%s%d\",",trav->token,idI);
idI++;
}
else if(strcmp(trav->token,"FLOATCONST")==0){
fprintf(fp1,"\"%s%d\",",trav->token,idF);
idF++;
}
else{
fprintf(fp1,"\"%s\",",trav->token);
}
}
fprintf(fp1,"\"%s\"\n",trav->token);
}
//printf("Information about Identifiers\n");
//int w = 0;
//for(w=0;w<16;w++){
//if(hashTable[w]!=NULL){
//listPoint = hashTable[w];
//while(listPoint!=NULL){
//printf("Table Index:%d\tName:%s\tLineno:%d\tDataType:%s\n",w,listPoint->name,listPoint->lineno,listPoint->type);
//listPoint = listPoint->next;
//}
//}
//}
int size = getSize(list);
char *a[size];
getArray(a,list);
int i;
//printf("obtained array\n");
//for(i=0;i<size;i++){
//printf("%s,",a[i]);
//}
fclose(fp);
fclose(fp1);
return 0;
}*/
