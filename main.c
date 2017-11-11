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

#define COMMAND 1;
#define SYMBOL 2;
#define END_CHAR 3;


const char *commands[] = {"if","else","for", "while", "do", "break", "continue",
	"return", "switch", "case", "default", "int", "char", "float", "double",
	"void", "struct", "typedef"};

const char *symbols[] = {"==", "<=", ">=", "!=", "<", ">", "=", "{", "}",
	"(", ")", "[", "]", "&&", "&", "||", "|", "+", "-", "*", "/"};

const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
	"l", "m" , "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
	"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
	"P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

const char *digits[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

const char *end_chars[] = {' ', '\n', '\t', ';'};

int identifyToken(char *word);
int isCommand(char *word);
int isSymbol(char *word);
int tokenFound(char *word, char *type);
int endCharFound(char *word);

int main(int argc, const char * argv[]) {
	char* input_file_name;
	FILE *input_file;
	char word[256] = "";
	int token_type;
	char input_char;

	input_file_name = "input_file";
	input_file = fopen(input_file_name, "rt");
	// le todo o arquivo de entrada ate encontrar EOF (end of file)
	while ((input_char = fgetc(input_file)) != EOF) {
		strncat(word, &input_char,1); //concatena o caractere lido ao final da word
		// printf("i:%c w:%s\n", input_char, word); //debug
		if (strchr(end_chars, input_char)) {
			endCharFound(word);
		} else {
			token_type = identifyToken(word);
			if (token_type != 0) {
				// token_type == 0 significa que nao foi possivel identificar o token
				// printf("token type: %d\n", token_type);
			}
		}
	}

	fclose(input_file);
  return 0;
}
// deve ser possivel identificar um identificador em "identifier=1"
// ao saber q "i" eh uma palavra, o programa deve continuar incrementando o word
// ate que ele encontre que "identifier=" nao esta presente na linguagem, quebrando
// o word em 2
int identifyToken(char *word) {
	if (isCommand(word)) {
		tokenFound(word, "Comando");
		return COMMAND;
	} else if (isSymbol(word)) {
		tokenFound(word, "Simbolo");
		return SYMBOL;
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

int tokenFound(char *word, char *type){
	printf("Achou %s: %s\n", type, word);
	memset(word, 0, strlen(word));
	return 0;
}

int endCharFound(char *word) {
	int last_char_pos = strlen(word) - 1;
	char end_char = word[last_char_pos]; // guarda o ultimo char
	word[last_char_pos] = 0; // remove o ultimo char
	int type = identifyToken(word); // identifica o token anterior ao end_char

	if(type==0){
		// TODO: so deve cair aqui caso o token antes do end_char nao fazer parte  da linguage
		// quando  a implemntacao de todos os reconhecedores estiver completa, essa parte deve
		// causar um erro, por enquanto so estou ignorando o token anterior
		memset(word, 0, strlen(word));
	}
	tokenFound(&end_char, "end char");
	return type;
}
