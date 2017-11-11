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

char input[] = "for (int a = 0; a < 10; a++) { if (a == 6) return; }";

const char *commands[] = {"if","else","for", "while", "do", "break", "continue", "return", "switch", "case", "default", "int", "char", "float", "double", "void", "struct", "typedef"};

const char *symbols[] = {"==", "<=", ">=", "!=", "<", ">", "=", "{", "}", "(", ")", "[", "]", "&&", "&", "||", "|", "+", "-", "%", "*", "/"};

const char *letters[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m" , "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

const char *numbers[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

const char end_chars[] = {' ', '\n', ';'};

int isCommand(char *word);
int isSymbol(char *word);

int main(int argc, const char * argv[]) {
	char word[256];
	int w_i = 0;
	char **tokens;
	for (int i = 0; i < sizeof(input); i++) {
		if (strchr(end_chars, input[i])) {
			if (isCommand(word)) {
				printf("Achou comando: %s\n", word);
			} else if (isSymbol(word)) {
				printf("Achou simbolo: %s\n", word);
			}
			memset(word,0,strlen(word));
			w_i = 0;
			continue;
		}
		word[w_i] = input[i];
		w_i++;
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