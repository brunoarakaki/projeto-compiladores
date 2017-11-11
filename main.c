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

const char *end_chars[] = {' ', '\n', ';'};


int isCommand(char *word);
int isSymbol(char *word);
int tokenFound(char *word, char *type);

int main(int argc, const char * argv[]) {
	char* input_file_name;
	FILE *input_file;
	char word[256];
	int w_i = 0;
	char **tokens;
	int input_char;

	input_file_name = "input_file";
	input_file = fopen(input_file_name, "rt");

	// le todo o arquivo de entrada ate encontrar EOF (end of file)
	while ((input_char = fgetc(input_file)) != EOF) {
		word[w_i] = input_char;
		//printf("%c --(%d) %s\n", input_char, w_i, word);
		w_i++;
		if (strchr(end_chars, input_char)) {
			w_i = tokenFound(word, "end_char");
		} else if (isCommand(word)) {
			w_i = tokenFound(word, "Comando");
		} else if (isSymbol(word)) {
			w_i = tokenFound(word, "Simbolo");
		}
	}

	fclose(input_file);
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
	memset(word,0,strlen(word));
	return 0;
}
