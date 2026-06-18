#include "ast.h"

static void PrintNB(ast *p, char * indent);
static void PrintOP(ast *p, char * indent);
static void PrintID(ast *p, char * indent);
static void PrintAFFEC(ast *p, char *indent);
static void PrintAFFICHER(ast *p, char *indent);
static void PrintTQ(ast *p, char *indent);
static void PrintCOMP(ast *p, char *indent);
static void PrintSI(ast *p, char *indent);


ast * CreerFeuilleNB(int nb){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_NB;
  strcpy(p->type_str,"NB");
  p->valeur = nb;
  return p;
}

ast * CreerFeuilleID(char* id){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_ID;
  strcpy(p->type_str,"ID");
  strcpy(p->str,id);
  return p;
}

ast * CreerNoeudOP(int op,ast* p1, ast*p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_OP;
  strcpy(p->type_str,"OP");
  p->operateur = op;
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
  }
  
ast * CreerNoeudAFFEC(ast* p1, ast*p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_AFFEC;
  strcpy(p->type_str,"AFFEC");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
  }
  
ast * CreerNoeudLINST(ast* p1, ast*p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_LINST;
  strcpy(p->type_str,"LINST");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
  }
  
ast * CreerNoeudAFFICHER(ast* p1){
	ast* p;
	INIT_NOEUD(p);
  	p->type = AST_AFFICHER;
  	strcpy(p->type_str,"AFFCIHER");
  	p->noeud[0]=p1;
  	return p;

}

ast * CreerNoeudTQ(ast* p1, ast*p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_TQ;
  strcpy(p->type_str,"TANTQUE");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
  }


ast * CreerNoeudCOMP(int op,ast* p1, ast*p2){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_COMP;
  strcpy(p->type_str,"COMP");
  p->operateur = op;
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  return p;
  }
  
ast * CreerNoeudSI(ast* p1, ast*p2, ast* p3){
  ast * p;
  INIT_NOEUD(p);
  p->type = AST_SI;
  strcpy(p->type_str,"SI");
  p->noeud[0] = p1;
  p->noeud[1] = p2;
  p->noeud[2] = p3;
  return p;
  }

void FreeAst(ast * p){
  if (p == NULL) return;
  free(p);
}

void Codelen(ast* p){
	if (p == NULL) return;
	switch(p->type){
		case AST_NB:
			//printf("\n\tpasser par code len NB\n");
			p->len += 2;
			break;
		case AST_OP:
			//printf("\n\tpasser par code len OP\n");
			Codelen(p->noeud[0]);
			Codelen(p->noeud[1]);
			p->len = p->len + 3 + p->noeud[0]->len + p->noeud[1]->len;
			break;
		case AST_ID:
			//printf("\n\tpasser par code len ID\n");
			p->len += 2;
			break;
		case AST_AFFEC:
			//printf("\n\tpasser par code len AFFECT\n");
			Codelen(p->noeud[1]);
			p->len = p->len + 2 + p->noeud[1]->len;
			break;
		case AST_LINST:
			//printf("\n\tpasser par code len LINST\n");
			Codelen(p->noeud[0]);
			Codelen(p->noeud[1]);
			p->len = p->len + (p->noeud[1] == NULL?0:p->noeud[1]->len) + p->noeud[0]->len;
			
			break;
		case AST_AFFICHER:
			//printf("\n\tpasser par code len AFFICHER\n");
			Codelen(p->noeud[0]);
			p->len = p->len + 2 + p->noeud[0]->len;
			break;
		case AST_TQ:
			// A completer apres codegen TQ
			//printf("\n\tpasser par code len TQ\n");
			Codelen(p->noeud[0]);
			Codelen(p->noeud[1]);
			p->len = p->len + 2 + p->noeud[0]->len + p->noeud[1]->len;
			break;
		case AST_COMP:
			//printf("\n\tpasser par code len COMP\n");
			Codelen(p->noeud[0]);
			Codelen(p->noeud[1]);
			p->len = p->len + 7 + p->noeud[0]->len + p->noeud[1]->len;
			break;
			
		case AST_SI:
			//printf("\n\tpasser par code len SI\n");
			Codelen(p->noeud[0]);
			Codelen(p->noeud[1]);
			Codelen(p->noeud[2]);
			p->len = p->len + 3 + p->noeud[0]->len + p->noeud[1]->len + p->noeud[2]->len;
			break;
			
		default:
			fprintf(stderr,"[Error] type <%d>: %s non reconnu\n",p->type,p->type_str);
			break;
	}
}


void PrintAst(ast * p){
  if (p == NULL) return;
  char indent[32] ="";
  switch(p->type){
  case AST_NB:
    PrintNB(p,indent);
    break;
  case AST_OP:
    PrintOP(p,indent);
    break;
  case AST_ID:
    PrintID(p,indent);
    break;
  case AST_AFFEC:
    PrintAFFEC(p,indent);
    break;
  case AST_LINST:
    PrintAst(p->noeud[0]);
    PrintAst(p->noeud[1]);
    break;
  case AST_AFFICHER:
  	PrintAFFICHER(p,indent);
    break;
  case AST_TQ:
  	PrintTQ(p,indent);
  	break;
  case AST_COMP:
  	PrintCOMP(p,indent);
    break;
  case AST_SI:
  	PrintSI(p,indent);
    break;
    
  default:
    fprintf(stderr,"[Error] type <%d>: %s non reconnu\n",p->type,p->type_str);
    break;
  }
}

void ErrorAst(const char * errmsg){
  fprintf(stderr,"[AST error] %s\n",errmsg);
  exit(1);
}

static void PrintNB(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Valeur: " TXT_NULL "%d\n",indent, p->valeur);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
}

static void PrintID(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "identificateur: " TXT_NULL "%s\n",indent, p->str);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
}

static void PrintOP(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Operateur: " TXT_NULL "%c\n",indent, p->operateur);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);  
  }
  
static void PrintAFFEC(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Affectation: " TXT_NULL "\n",indent);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);  
  }
  
static void PrintAFFICHER(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "Afficher: " TXT_NULL "\n",indent);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
  PrintAst(p->noeud[0]);  
  }  
  
static void PrintTQ(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "TANTQUE: " TXT_NULL "\n",indent);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);  
  }  

static void PrintCOMP(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "COMP: " TXT_NULL "\n",indent);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);  
  } 
  
static void PrintSI(ast *p, char *indent){
  printf("%s" TXT_BOLD TXT_BLUE "Noeud:  " TXT_NULL "%p\n",indent, p);
  printf("%s" TXT_BOLD "Type:   " TXT_NULL "%s\n",indent, p->type_str);
  printf("%s" TXT_BOLD "SI: " TXT_NULL "\n",indent);
  printf("%s" TXT_BOLD "Code len:   " TXT_NULL "%d\n",indent, p->len);
  PrintAst(p->noeud[0]);
  PrintAst(p->noeud[1]);
  PrintAst(p->noeud[2]);  
  } 


