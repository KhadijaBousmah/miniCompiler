#include "codegen.h"
extern int pile;  //premiere adresse libre 
extern FILE* exec; 
extern tablesymb TABLE;
int instr = 0;

void codegen(ast* p){
	if (p==NULL) return;
  	switch(p->type){
	  case AST_NB:
		codeNB(p);
		break;
	  case AST_OP:
		codeOP(p);
		break;
	  case AST_ID:
		codeID(p);
		break;
	 case AST_AFFEC:
		codeAF(p);
		break;
	case AST_LINST:
		codegen(p->noeud[0]);
		codegen(p->noeud[1]);
		break;
	case AST_AFFICHER:
		codeAFFICHER(p);
		break;
	case AST_TQ:
		codeTQ(p);
		break;
	case AST_COMP:
		codeCOMP(p);
		break;
		
	case AST_SI:
		codeSI(p);
		break;
		
	  default:
		fprintf(stderr,"[Erreur code gen] type <%d>: %s non reconnu\n",p->type,p->type_str);
		break;
  }
}

void codegenfin(ast* p){
	fprintf(exec,"STOP\n");
	instr += 1;
}

void codeNB(ast* p){
	fprintf(exec,"LOAD #%d\n",p->valeur);
	fprintf(exec,"STORE %d\n",pile++);
	instr += 2;
	
}



void codeID(ast* p){
	int adr = tsymb_retrouver(TABLE,p->str);
	fprintf(exec,"LOAD %d\n",adr);
	fprintf(exec,"STORE %d\n",pile++);
	instr += 2;
}

void codeOP(ast* p){
	codegen(p->noeud[0]);
	codegen(p->noeud[1]);
	fprintf(exec,"LOAD %d\n",pile-2);
	switch (p->operateur){
		case '+':
			fprintf(exec,"ADD %d\n",pile-1);break;
		case '*':
			fprintf(exec,"MUL %d\n",pile-1);break;
		case '-':
			fprintf(exec,"SUB %d\n",pile-1);break;
		case '/':
			fprintf(exec,"DIV %d\n",pile-1);break;
		case '%':
			fprintf(exec,"MOD %d\n",pile-1);break;
	}
	fprintf(exec,"STORE %d\n",pile-2);
	instr += 3;
	pile--;
	}
	
void codeAF(ast* p){
	int adr = tsymb_retrouver(TABLE,p->noeud[0]->str);
	codegen(p->noeud[1]);
	fprintf(exec,"LOAD %d\n",pile-1);
	fprintf(exec,"STORE %d\n",adr);
	instr += 2;
	pile--;
	}
	
	
void codeAFFICHER(ast* p){
	codegen(p->noeud[0]);
	
	fprintf(exec,"LOAD %d\n",pile-1);
	fprintf(exec,"WRITE \n");
	instr += 2;
	pile--;
	
	}
	
	
void codeTQ(ast* p){
	int debut = instr;
	codegen(p->noeud[0]);
	
	fprintf(exec,"LOAD %d\n",pile-1);
	pile--;

	int fin = debut + p->noeud[1]->len + p->noeud[0]->len + 2;
	
	fprintf(exec,"JUMZ %d\n",fin+1);
	codegen(p->noeud[1]);
	
	fprintf(exec,"JUMP %d\n",debut);
	instr += 3;
	
	}
	
void codeCOMP(ast* p){
	codegen(p->noeud[0]);
	codegen(p->noeud[1]);
	fprintf(exec,"LOAD %d\n",pile-2);
	fprintf(exec,"SUB %d\n",pile-1);
	pile--;
	switch (p->operateur){
		case '<':
			fprintf(exec,"JUML %d\n", instr+3);
			break;
			
		case '>':
			fprintf(exec,"JUMG %d\n", instr+3);
			break;
			
		case '=':
			fprintf(exec,"JUMZ %d\n", instr+3);
			break;
	}
	fprintf(exec,"LOAD #1 \n");
	fprintf(exec,"STORE %d\n",pile-1);
	fprintf(exec,"LOAD #0 \n");
	fprintf(exec,"STORE %d\n",pile-1);
	instr += 7;
	}
	
	
void codeSI(ast* p){
	codegen(p->noeud[0]);
	
	fprintf(exec,"LOAD %d\n",pile-1);
	pile--;

	int fin1 = instr + p->noeud[1]->len + 1;
	
	fprintf(exec,"JUMZ %d\n",fin1+1);
	codegen(p->noeud[1]);
	
	int fin2 = fin1 + + p->noeud[2]->len;
	fprintf(exec,"JUMP %d\n",fin2);
	instr += 3;

	}
	



