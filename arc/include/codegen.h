#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include "tsymb.h"



void codegen(ast* p);
void codeOP(ast* p);
void codeNB(ast* p);
void codeID(ast* p);
void codeAF(ast* p);
void codeAFFICHER(ast* p);
void codeTQ(ast* p);
void codeCOMP(ast* p);
void codeSI(ast* p);
void codegenfin(ast* p);


extern int pile;


#endif
