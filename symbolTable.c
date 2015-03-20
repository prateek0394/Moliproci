#include "lexer.h"
/*
Submitted By:
	Team - 24 Group - 1
	Prateek Jain	2012C6PS392P
	Vishal Goyal	2012A7PS071P
*/
	QUEUE s;
void push3 (struct parseNode *p)
{
    if (s.entry == (MAXSIZE - 1))
    {
        printf ("Stack is Full\n");
        return;
    }
    else
    {
       s.entry = s.entry + 1;
        s.q[s.entry] = p;
    }
    return;
}
struct parseNode *pop3 ()
{
    if (s.top == s.entry)
    {
        return NULL;
    }
    else
    {
		s.top = s.top + 1;
        return s.q[s.top];
     }
}

void fillFuncNames(struct parseNode *tree,struct idNode *symbolTable[]){
STACK s;

}

void insertID(struct idNode *ST[],char *name,char *type,int lineno,char *fname){
			int hIndex = h(name,strlen(name));
			struct idNode *id = ST[hIndex];
			if(ST[hIndex]==NULL){
				ST[hIndex] = (struct idNode *)malloc(sizeof(struct idNode));
				id = ST[hIndex];
			}else{
			while(id->next!=NULL){
			if(strcmp(id->name,name)==0 && strcmp(id->funcName,fname)==0){
				printf("**************Error*************\nwrong declaration in line %d\n",lineno);
				return;
			}
			id=id->next;
			}
			id->next = (struct idNode *)malloc(sizeof(struct idNode));
			id = id->next;
			}
			memset(id->name,'\0',strlen(name));
			strcpy(id->name,name);
			id->type = (char *)malloc(strlen(type));
			memset(id->type,'\0',strlen(type));
			strcpy(id->type,type);
			memset(id->funcName,'\0',strlen(fname));
			strcpy(id->funcName,fname);
			id->lineno = (struct lineNo *)malloc(sizeof(struct lineNo));
			id->lineno->lineno = lineno;			
}

void updateID(struct idNode *ST[],char *name,int lineno,char *fname){
	int hIndex = h(name,strlen(name));
	struct idNode *id = ST[hIndex];
	while(id!=NULL && (strcmp(id->name,name)!=0 || strcmp(id->funcName,fname)!=0) && (strcmp(id->name,name)!=0||strcmp(id->name,id->funcName)!=0)){
		id = id->next;
	}
	if(id==NULL){
		printf("********************Undeclared variable in line %d\t variable:%s*******************\n",lineno,name);
		return;
	}else{
		struct lineNo *x = id->lineno;
		while(x->next!=NULL){
			if(x->lineno==lineno){
				return;
			}else
				x = x->next;
		}
		x->next = (struct lineNo *)malloc(sizeof(struct lineNo));
		x = x->next;
		x->lineno = lineno;
	}
}
void fillType(struct parseNode *tree,struct idNode *symbolTable[],struct lineNode *list){}

void abc(struct parseNode *t){
printf("%s\n",t->name);
for(t=t->down;t!=NULL;t=t->next)
abc(t);

}


void recCreateST(struct parseNode *trav,struct idNode *ST[],struct lineNode *list,char *fname){
//struct parseNode *child;
	//child = trav->down;
//	printf("Node:%s\n",trav->name);
	if(strcmp(trav->name,"<function>")==0){
		struct parseNode *x = trav->down;
		if(strcmp(x->name,"INIT")==0)
		strcpy(fname,x->name);
		else
			strcpy(fname,x->val);
}else if(trav->name[0]=='I' && trav->name[1]=='D'){
		char name[255];
		memset(name,'\0',255);
		int r;
		for(r=0;r<strlen(trav->val) && trav->val[r]!='.';r++){	
		name[r] = trav->val[r];
	}
		//printf("HERE\n");
		if(strcmp(trav->parent->name,"<declStnt>")==0 || strcmp(trav->parent->name,"<furID>")==0 || strcmp(trav->parent->name,"<paramList>")==0 || strcmp(trav->parent->name,"<function>")==0){
	//		printf("HERE1\n");
			int lno = trav->lineno;
			struct lineNode *x = list;
			while(x->no<lno-1){
				x = x->next;
			}

			struct tokenNode *tn = x->tokenList;
			int y = 0;
			while(tn!=NULL)	{
				y++;
				tn=tn->next;
			}	
			tn = x->tokenList;
		
			struct tokenNode *arr[y];
			y = 0;
			while(tn!=NULL && ( tn->value == NULL || strcmp(tn->value,trav->val)!=0)){				
				arr[y++] = tn;
				tn = tn->next;
			}
			//if(y==0)
			//continue;
			y =y-1;
			if(strcmp(arr[y]->token,"SMC")==0){
				while(strcmp(arr[y]->token,"ID") == 0  || strcmp(arr[y]->token,"SMC") == 0)y=y-1;	
			}
			//type,name,lineno,fname
	//		printf("%s\t%s\t%s\t%d\n",trav->val,arr[y]->token,fname,trav->lineno);
			insertID(ST,name,arr[y]->token,trav->lineno,fname);
		}else if(strcmp(trav->parent->name,"ASSIGN")==0){
			int lno = trav->lineno;
			//printf("lno%d\n",lno);
			struct lineNode *x = list;
			while(x->no < lno-1){
				x = x->next;
			}
			struct tokenNode *tn = x->tokenList;
			//printf("%s\n",tn->token);
			struct tokenNode *tn1 = NULL;				
			while(tn!=NULL && ( tn->value == NULL || strcmp(tn->value,trav->val)!=0)){
				tn1 = tn;				
				tn = tn->next;

			}
			if(tn1!=NULL && (strcmp(tn1->token,"OBJECT")==0||strcmp(tn1->token,"FLOAT")==0||strcmp(tn1->token,"INT")==0||strcmp(tn1->token,"VECTOR")==0||strcmp(tn1->token,"LNR")==0)){
					//		printf("HERE4\n");				
				insertID(ST,name,tn1->token,trav->lineno,fname);
		//		printf("%s\t%s\t%s\t%d\n",trav->val,tn1->token,fname,trav->lineno);

			}else{
				//printf("HERE5\n");
				updateID(ST,name,trav->lineno,fname);
			//	printf("Update%s\t%s\t%d\n",trav->val,fname,trav->lineno);
			}
							
		}else{
			updateID(ST,name,trav->lineno,fname);
			//printf("Update2%s\t%s\t%d\n",trav->val,fname,trav->lineno);
//printf("HERE3\n");
		}
	}
for(trav = trav->down;trav!=NULL;trav=trav->next)recCreateST(trav,ST,list,fname);	
}
