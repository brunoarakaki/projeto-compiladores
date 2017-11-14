//
//  main.c
//  Compiladores
//
//  Created by Mayer Levy on 11/13/17.
//  Copyright © 2017 Mayer Levy. All rights reserved.
//

#include "main.h"
#include "analisador_lexico.h"
#include "analisador_sintatico.h"

int main(int argc, const char * argv[]) {
	ListaToken* tokens = analiseLexica();
	analiseSintatica(tokens);
	return 0;
}