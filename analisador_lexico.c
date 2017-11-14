//
//  main.c
//  Compiladores
//
//  Created by Mayer Levy on 10/1/17.
//  Copyright © 2017 Mayer Levy. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "analisador_lexico.h"

const char *commands[] = {"prog", "se","senao","para", "enquanto", "faca", "quebra", "continue",
	"retorna", "seleciona", "caso", "padrao", "int", "char", "float", "double", "verdadeiro", "falso", 
	"void", "struct", "typedef"};

const char *symbols[] = {"==", "<=", ">=", "!=", "<", ">", "=", "{", "}",
	"(", ")", "[", "]", "&&", "&", "||", "|", "+", "-", "*", "/", ";"};

const char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
	'l', 'm' , 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

const char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

const char *end_chars[] = {" ", "\n", "\t"};

ListaToken pilhaToken;
int found_tokens = 0;

ListaToken* analiseLexica() {
	char* input_file_name;
	FILE *input_file;
	char word[256] = "";
	int token_type = 0;
	int last_token_type = 0;
	char input_char;
	
	input_file_name = "input_file";
	input_file = fopen(input_file_name, "rt");
	// le todo o arquivo de entrada ate encontrar EOF (end of file)
	while ((input_char = fgetc(input_file)) != EOF) {
		last_token_type = token_type;
		strncat(word, &input_char, 1); //concatena o caractere lido ao final da word
		token_type = identifyToken(word);
		if (token_type == 0) {
			word[strlen(word)-1] = 0; // remove o ultimo char
			newTokenFound(word, last_token_type);
			strncat(word, &input_char, 1); //concatena o caractere lido ao final da word
			token_type = identifyToken(word);
		}
	}
	token_type = identifyToken(word);
	if (token_type != 0) {
		newTokenFound(word, token_type);
	}
	fclose(input_file);
	return &pilhaToken;
}

int identifyToken(char *word) {
	if (isCommand(word)) {
		return COMMAND;
	} else if (isSymbol(word)) {
		return SYMBOL;
	} else if (isWord(word)) {
		return WORD;
	} else if (isNumber(word)) {
		return NUMBER;
	} else if (isEndChar(word)) {
		return END_CHAR;
	}
	return 0;
}

int isCommand(char *word) {
	for (int j = 0; j < sizeof(commands)/sizeof(*commands); j++) {
		if (strcmp(word, commands[j]) == 0) {
			return 1;
		}
	}
	return 0;
}

int isSymbol(char *word) {
	for (int j = 0; j < sizeof(symbols)/sizeof(*symbols); j++) {
		if (strcmp(word, symbols[j]) == 0) {
			return 1;
		}
	}
	return 0;
}

int isLetter(char word) {
	for (int j = 0; j < sizeof(letters)/sizeof(*letters); j++) {
		if (word == letters[j]) {
			return 1;
		}
	}
	return 0;
}

int isWord(char *word) {
	if (strlen(word) == 0) return 0;
	for (int j = 0; j < strlen(word); j++) {
		if (!isLetter(word[j])) {
			return 0;
		}
	}
	return 1;
}

int isCharacter(char *word) {
	if (strlen(word) != 3) return 0;
	if (word[0] == '\'' && isLetter(word[1]) && word[2] == '\'') {
		return 1;
	}
	return 0;
}

int isDigit(char word) {
	for (int j = 0; j < sizeof(digits)/sizeof(*digits); j++) {
		if (word == digits[j]) {
			return 1;
		}
	}
	return 0;
}

int isNumber(char *word) {
	if (strlen(word) == 0) return 0;
	for (int j = 0; j < strlen(word); j++) {
		if (!isDigit(word[j])) {
			return 0;
		}
	}
	return 1;
}

int isEndChar(char *word) {
	for (int j = 0; j < sizeof(end_chars)/sizeof(*end_chars); j++) {
		if (strcmp(word, end_chars[j]) == 0) {
			return 1;
		}
	}
	return 0;
}

int isString(char *word) {
	char *string = word;
	string++;
	string[strlen(string)-1] = '\0';
	if (word[0] == '\'' && isWord(string) && word[2] == '\'') {
		return 1;
	}
	return 0;
}

int registerToken(char *word, char *type){
	printf("Achou %s: %s\n", type, word);
	found_tokens++;
	Token* new_token = malloc(sizeof(Token));
	strcpy(new_token->value, word);
	strcpy(new_token->type, type);
	adicionaToken(&pilhaToken, new_token);
	memset(word, 0, strlen(word));
	return 0;
}

int newTokenFound(char *word, int type) {
	
	if (type == COMMAND) {
		registerToken(word, "COMANDO");
	} else if (type == SYMBOL) {
		registerToken(word, "SIMBOLO");
	} else if (type == WORD) {
		registerToken(word, "IDENTIFICADOR");
	} else if (type == NUMBER) {
		registerToken(word, "NUMERO");
	}
	memset(word, 0, strlen(word));
	return type;
}

void adicionaToken(ListaToken* pilha, Token* token) {
	for (int i = 0; i < sizeof(pilha->tokens)/sizeof(pilha->tokens[0]); i++) {
		if (pilha->tokens[i] == NULL) {
			pilha->tokens[i] = token;
			return;
		}
	}
}

Token* removeToken(ListaToken *pilha) {
	for (int i = 0; i < sizeof(pilha->tokens)/sizeof(pilha->tokens[0]); i++) {
		if (pilha->tokens[i] != NULL) {
			Token* retorno = pilha->tokens[i];
			pilha->tokens[i] = NULL;
			return retorno;
		}
	}
	return NULL;
}

int listaTokenVazia(ListaToken *pilha) {
	for (int i = 0; i < sizeof(pilha->tokens)/sizeof(Token*); i++) {
		if (pilha->tokens[i] != NULL) {
			return 0;
		}
	}
	return 1;
}
