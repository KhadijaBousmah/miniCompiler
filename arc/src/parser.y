%{
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  
  #include "ast.h"
  #include "codegen.h"
  #include "tsymb.h"
    
  extern int yylex();
  static void print_file_error(char * s, char *errmsg);

  struct ast * ARBRE_ABSTRAIT = NULL;

  void yyerror(const char * s);

  char srcname[64];
  char exename[64] = "a.out";
  FILE * exec;
  
  int pile;
  tablesymb TABLE;
%}

%union{
  int nb;
  struct ast* arbre;
  char id[32];
 };

%define parse.error detailed
%locations

%token <nb> NB
%token <id> ID
%token AFFECT "<-"
%token DECLA
%token AFFICHER 
%token TQ FAIRE FTQ
%token SI ALORS SINON FSI
%left '<' '>' '=' 
%left '+' '-' 
%left '/' '*' '%'
%start PROGRAMME

%type <arbre> COMP
%type <arbre> EXP
%type <arbre> INST
%type <arbre> AFFECTATION
%type <arbre> LINST
%type <arbre> TANTQUE
%type <arbre> SI_SINON

%%

PROGRAMME: DECLARATION LINST{Codelen($2);
							PrintAst($2);
							pile = adr;
							printf("%d\n",pile);
							
	     					codegen($2);
	     					codegenfin($2);} 
|LINST  {Codelen($1);
		PrintAst($1);
	    codegen($1);
	     codegenfin($1);}
	     
DECLARATION: DECLA IDS {}

IDS: ID';' {tsymb_ajouter(TABLE, $1);}
|ID','IDS  {tsymb_ajouter(TABLE, $1);}     
	
LINST : INST  	{$$=CreerNoeudLINST($1,NULL);} 
| INST LINST   {$$=CreerNoeudLINST($1,$2);}

INST : COMP ';' {$$=$1;}
| AFFECTATION {$$=$1;}
| AFFICHER COMP ';'  {$$=CreerNoeudAFFICHER($2);}
| TANTQUE  {$$=$1;}
| SI_SINON  {$$=$1;}

AFFECTATION : ID "<-" COMP ';' {$$=CreerNoeudAFFEC(CreerFeuilleID($1),$3);}

TANTQUE : TQ COMP FAIRE LINST FTQ {$$=CreerNoeudTQ($2,$4);}

SI_SINON : SI COMP ALORS LINST SINON LINST FSI {$$=CreerNoeudSI($2,$4,$6);}

COMP : EXP {$$=$1;}
| EXP '<' EXP {$$=CreerNoeudCOMP('<',$1,$3);}
| EXP '>' EXP {$$=CreerNoeudCOMP('>',$1,$3);}
| EXP '=' EXP {$$=CreerNoeudCOMP('=',$1,$3);}


EXP : NB    {$$ = CreerFeuilleNB($1);}
| EXP '+' EXP {$$=CreerNoeudOP('+',$1,$3);}
| EXP '*' EXP {$$=CreerNoeudOP('*',$1,$3);}
| EXP '/' EXP {$$=CreerNoeudOP('/',$1,$3);}
| EXP '%' EXP {$$=CreerNoeudOP('%',$1,$3);}
| EXP '-' EXP {$$=CreerNoeudOP('-',$1,$3);}
| '(' EXP ')' {$$=$2;}
| ID {$$=CreerFeuilleID($1);}
;

%%

int main( int argc, char * argv[] ) {
  extern FILE *yyin;
  
  if (argc > 1){
    strcpy(srcname, argv[1]);
    if ( (yyin = fopen(srcname,"r"))==NULL ){
      char errmsg[256];
      sprintf(errmsg,"fichier \x1b[1m\x1b[33m' %s '\x1b[0m introuvable",srcname);
      print_file_error(argv[0],errmsg);
      exit(1);
    }
  }  else {
    print_file_error(argv[0],"aucun fichier en entree");
    exit(1);
  }
  if (argc == 3){
    strcpy(exename, argv[2]);
  }
  exec = fopen(exename,"w");
  tsymb_init(TABLE);
  
  yyparse();
  tsymb_print(TABLE);
  fclose(yyin);
}



static void print_file_error(char * prog, char *errmsg){
  fprintf(stderr,
	  "\x1b[1m%s:\x1b[0m \x1b[31m\x1b[1merreur fatale:\x1b[0m %s\nechec de la compilation\n",
	  prog, errmsg);
}

void yyerror(const char * s)
{
  fprintf(stderr, "\x1b[1m%s:%d:%d:\x1b[0m %s\n", srcname, yylloc.first_line, yylloc.first_column, s);
  exit(0);
}
