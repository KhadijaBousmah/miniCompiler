#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  TXT_RED    "\x1b[31m"
#define  TXT_GREEN  "\x1b[32m"
#define  TXT_BLUE   "\x1b[34m"
#define  TXT_BOLD   "\x1b[1m"
#define  TXT_NULL   "\x1b[0m"

#define INIT_NOEUD(p)   if ((p = malloc(sizeof(ast))) == NULL)	\
    ErrorAst("echec allocation mémoire");			\
  else {							\
    p->type = 0;						\
    p->type_str[0] = '\0';					\
    p->valeur = 0;						\
    p->len = 0;    				\
  }								\

enum {AST_NB = 256, AST_OP, AST_ID,AST_AFFEC, AST_LINST, AST_AFFICHER, AST_TQ, AST_COMP, AST_SI} ;

typedef struct ast{
  int  type;
  char type_str[32];
  int valeur;
  int operateur;
  struct ast* noeud[3];
  char str[32];
  int len;
} ast;


ast * CreerFeuilleNB(int nb);

ast * CreerNoeudAFFICHER(ast* p1);

ast* CreerNoeudOP(int op, ast* p1, ast* p2);

ast* CreerNoeudCOMP(int op, ast* p1, ast* p2);

ast* CreerFeuilleID(char* id);

ast* CreerNoeudAFFEC( ast* p1, ast* p2);

ast* CreerNoeudLINST( ast* p1, ast* p2);

ast* CreerNoeudTQ( ast* p1, ast* p2);

ast* CreerNoeudSI(ast* p1, ast* p2, ast* p3);

void FreeAst(ast * p);

void PrintAst(ast * p);

void Codelen(ast *p);

void ErrorAst(const char * errmsg);


#endif
