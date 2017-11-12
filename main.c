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

#define COMMAND 1
#define SYMBOL 2
#define WORD 3
#define NUMBER 4
#define END_CHAR 5


const char *commands[] = {"if","else","for", "while", "do", "break", "continue",
	"return", "switch", "case", "default", "int", "char", "float", "double",
	"void", "struct", "typedef"};

const char *symbols[] = {"==", "<=", ">=", "!=", "<", ">", "=", "{", "}",
	"(", ")", "[", "]", "&&", "&", "||", "|", "+", "-", "*", "/"};

const char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
	'l', 'm' , 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '\0'};

const char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

const char *end_chars[] = {" ", "\n", "\t", ";"};

char *tokens[1024];
int found_tokens = 0;

int identifyToken(char *word);
int isCommand(char *word);
int isSymbol(char *word);
int isWord(char *word);
int isNumber(char *word);
int isEndChar(char *word);
int registerToken(char *word, char *type);
int newTokenFound(char *word, int type);

int main(int argc, const char * argv[]) {
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
	fclose(input_file);
	return 0;
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

int registerToken(char *word, char *type){
	printf("Achou %s: %s\n", type, word);
	found_tokens++;
	char *new_token = malloc(sizeof(char *));
	strcpy(new_token, word);
	tokens[found_tokens - 1] = new_token;
	memset(word, 0, strlen(word));
	return 0;
}

int newTokenFound(char *word, int type) {
	
	if (type == COMMAND) {
		registerToken(word, "Comando");
		memset(word, 0, strlen(word));
	} else if (type == SYMBOL) {
		registerToken(word, "Simbolo");
		memset(word, 0, strlen(word));
	} else if (type == WORD) {
		registerToken(word, "Identificador");
		memset(word, 0, strlen(word));
	} else if (type == NUMBER) {
		registerToken(word, "Numero");
		memset(word, 0, strlen(word));
	} else if(type == END_CHAR){
		registerToken(word, "End char");
		memset(word, 0, strlen(word));
	}
	return type;
}
