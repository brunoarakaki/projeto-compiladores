//
//  analisador_lexico.h
//  Compiladores
//
//  Created by Mayer Levy on 11/13/17.
//  Copyright © 2017 Mayer Levy. All rights reserved.
//

#ifndef analisador_lexico_h
#define analisador_lexico_h

#define COMMAND 1
#define SYMBOL 2
#define WORD 3
#define NUMBER 4
#define END_CHAR 5

typedef struct {
	char type[256];
	char value[256];
} Token;

typedef struct {
	Token *tokens[256];
} ListaToken;

void adicionaToken(ListaToken* pilha, Token* token);
Token* removeToken(ListaToken *pilha);
int listaTokenVazia(ListaToken *pilha);

int identifyToken(char *word);
int isCommand(char *word);
int isSymbol(char *word);
int isWord(char *word);
int isNumber(char *word);
int isEndChar(char *word);
int registerToken(char *word, char *type);
int newTokenFound(char *word, int type);

ListaToken* analiseLexica();

#endif /* analisador_lexico_h */
