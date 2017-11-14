//
//  analisador_sintatico.c
//  
//
//  Created by Mayer Levy on 11/12/17.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analisador_lexico.h"
#include "analisador_sintatico.h"

Token* token_atual;

MaquinaEstados maq_prog;
MaquinaEstados maq_declaracoes;
MaquinaEstados maq_declaracao;
MaquinaEstados maq_comandos;
MaquinaEstados maq_comando;
MaquinaEstados maq_tipo;
MaquinaEstados maq_identificador;
MaquinaEstados maq_atribuicao;
MaquinaEstados maq_operando;
MaquinaEstados maq_expressao;
MaquinaEstados maq_numero;
MaquinaEstados maq_caractere;
MaquinaEstados maq_exparitmetica;
MaquinaEstados maq_string;
MaquinaEstados maq_expbool;
MaquinaEstados maq_condicao;
MaquinaEstados maq_iteracao;
MaquinaEstados maq_chamadafuncao;
MaquinaEstados maq_entrada;
MaquinaEstados maq_saida;
MaquinaEstados maq_operadorarit;
MaquinaEstados maq_operadorlogico;
MaquinaEstados maq_expcondicao;
MaquinaEstados maq_operadorcond;
MaquinaEstados maq_funcao;
MaquinaEstados maq_argumentos;
MaquinaEstados maq_retorno;

void analiseSintatica(ListaToken *tokens) {
	
	iniciaMaquinas();
	
	token_atual = removeToken(tokens);
	if (executaMaquina(&maq_prog, tokens)) {
		printf("Código fonte VÁLIDO\n");
	} else {
		printf("Código fonte INVÁLIDO\n");
	}
	
}

int executaMaquina(MaquinaEstados* maq, ListaToken *pilhaTokens) {
	int tok_id = classificaToken(token_atual);
	while (maq->transicao_atual < maq->num_transicoes && token_atual != NULL) {
		tok_id = classificaToken(token_atual);
		Transicao *t = &maq->transicoes[maq->transicao_atual];
		if (t->est_origem == maq->est_atual) {
			if (t->token_id == TOK_NULL) {
				MaquinaEstados *nova_maq = malloc(sizeof(MaquinaEstados));
				memcpy(nova_maq, t->maq_destino, sizeof(MaquinaEstados));
				semantico_tbd();
				if (executaMaquina(nova_maq, pilhaTokens)) {
					maq->est_atual = t->est_destino;
					if (maq->transicao_atual < maq->num_transicoes) {
						maq->transicao_atual = -1;
					}
				};
			} else if (t->token_id == tok_id) {
				maq->est_atual = t->est_destino;
				token_atual = removeToken(pilhaTokens);
				semantico_tbd();
				maq->transicao_atual = -1;
			}
		}
		maq->transicao_atual++;
	}
	if (maq->est_atual == maq->est_final[0] || maq->est_atual == maq->est_final[1]) {
		return 1;
	} else {
		return 0;
	}
}

void iniciaMaquinas() {
	iniciaMaqProg();
	iniciaMaqDeclaracoes();
	iniciaMaqDeclaracao();
	iniciaMaqTipo();
	iniciaMaqComandos();
	iniciaMaqComando();
	iniciaMaqIdentificador();
	iniciaMaqAtribuicao();
	iniciaMaqOperando();
	iniciaMaqExpressao();
	iniciaMaqCaractere();
	iniciaMaqNumero();
	iniciaMaqExparitmetica();
	iniciaMaqString();
	iniciaMaqOperadorarit();
	iniciaMaqOperadorlogico();
	iniciaMaqExpbool();
	iniciaMaqCondicao();
	iniciaMaqExpcondicao();
	iniciaMaqOperadorcond();
	iniciaMaqIteracao();
	iniciaMaqChamadafuncao();
	iniciaMaqFuncao();
	iniciaMaqArgumentos();
	iniciaMaqRetorno();
	iniciaMaqEntrada();
	iniciaMaqSaida();
}

void iniciaMaqProg() {
	
	maq_prog.num_estados = 5;
	maq_prog.nome = "PROG";
	
	criaTransicao(&maq_prog, TOK_PROG, NULL, 0, 1);
	criaTransicao(&maq_prog, TOK_CHAVES_ABRE, NULL, 1, 2);
	criaTransicao(&maq_prog, TOK_NULL, &maq_declaracoes, 2, 3);
	criaTransicao(&maq_prog, TOK_NULL, &maq_comandos, 3, 4);
	criaTransicao(&maq_prog, TOK_CHAVES_FECHA, NULL, 4, 5);
	criaTransicao(&maq_prog, TOK_NULL, &maq_funcao, 5, 5);
	
	maq_prog.est_final[0] = 5;
	maq_prog.est_final[1] = -1;
	maq_prog.est_atual = 0;
	maq_prog.transicao_atual = 0;
	
}

void iniciaMaqDeclaracoes() {
	
	maq_declaracoes.num_estados = 2;
	maq_declaracoes.nome = "DECLARACOES";
	
	criaTransicao(&maq_declaracoes, TOK_NULL, &maq_declaracao, 0, 1);
	criaTransicao(&maq_declaracoes, TOK_NULL, &maq_declaracao, 1, 1);
	
	maq_declaracoes.est_final[0] = 1;
	maq_declaracoes.est_final[1] = -1;
	maq_declaracoes.est_atual = 0;
	maq_declaracoes.transicao_atual = 0;
	
}

void iniciaMaqDeclaracao() {
	
	maq_declaracao.num_estados = 4;
	maq_declaracao.nome = "DECLARACAO";
	
	criaTransicao(&maq_declaracao, TOK_NULL, &maq_tipo, 0, 1);
	criaTransicao(&maq_declaracao, TOK_NULL, &maq_identificador, 1, 2);
	criaTransicao(&maq_declaracao, TOK_PONTO_VIRGULA, NULL, 2, 3);
	
	maq_declaracao.est_final[0] = 3;
	maq_declaracao.est_final[1] = -1;
	maq_declaracao.est_atual = 0;
	maq_declaracao.transicao_atual = 0;
	
}

void iniciaMaqTipo() {
	
	maq_tipo.num_estados = 2;
	maq_tipo.nome = "TIPO";
	
	criaTransicao(&maq_tipo, TOK_INT, NULL, 0, 1);
	criaTransicao(&maq_tipo, TOK_CHAR, NULL, 0, 1);
	criaTransicao(&maq_tipo, TOK_STRING, NULL, 0, 1);
	criaTransicao(&maq_tipo, TOK_FLOAT, NULL, 0, 1);
	criaTransicao(&maq_tipo, TOK_BOOL, NULL, 0, 1);
	
	maq_tipo.est_final[0] = 1;
	maq_tipo.est_final[1] = -1;
	maq_tipo.est_atual = 0;
	maq_tipo.transicao_atual = 0;
	
}

void iniciaMaqComandos() {
	
	maq_comandos.num_estados = 2;
	maq_comandos.nome = "COMANDOS";
	
	criaTransicao(&maq_comandos, TOK_NULL, &maq_comando, 0, 1);
	criaTransicao(&maq_comandos, TOK_NULL, &maq_comando, 1, 1);
	
	maq_comandos.est_final[0] = 1;
	maq_comandos.est_final[1] = -1;
	maq_comandos.est_atual = 0;
	maq_comandos.transicao_atual = 0;
	
}

void iniciaMaqComando() {
	
	maq_comando.num_estados = 2;
	maq_comando.nome = "COMANDO";
	
	criaTransicao(&maq_comando, TOK_NULL, &maq_atribuicao, 0, 1);
	criaTransicao(&maq_comando, TOK_NULL, &maq_condicao, 0, 1);
	criaTransicao(&maq_comando, TOK_NULL, &maq_iteracao, 0, 1);
	criaTransicao(&maq_comando, TOK_NULL, &maq_chamadafuncao, 0, 1);
	criaTransicao(&maq_comando, TOK_NULL, &maq_entrada, 0, 1);
	criaTransicao(&maq_comando, TOK_NULL, &maq_saida, 0, 1);
	criaTransicao(&maq_comando, TOK_NULL, &maq_retorno, 0, 1);
	
	maq_comando.est_final[0] = 1;
	maq_comando.est_final[1] = -1;
	maq_comando.est_atual = 0;
	maq_comando.transicao_atual = 0;
	
}

void iniciaMaqIdentificador() {
	maq_identificador.num_estados = 2;
	maq_identificador.nome = "IDENTIFICADOR";
	
	criaTransicao(&maq_identificador, TOK_ID, NULL, 0, 1);
	
	maq_identificador.est_final[0] = 1;
	maq_identificador.est_final[1] = -1;
	maq_identificador.est_atual = 0;
	maq_identificador.transicao_atual = 0;
}

void iniciaMaqAtribuicao() {
	maq_atribuicao.num_estados = 5;
	maq_atribuicao.nome = "ATRIBUICAO";
	
	criaTransicao(&maq_atribuicao, TOK_NULL, &maq_identificador, 0, 1);
	criaTransicao(&maq_atribuicao, TOK_IGUAL, NULL, 1, 2);
	criaTransicao(&maq_atribuicao, TOK_NULL, &maq_expressao, 2, 3);
	criaTransicao(&maq_atribuicao, TOK_PONTO_VIRGULA, NULL, 3, 4);
	
	maq_atribuicao.est_final[0] = 4;
	maq_atribuicao.est_final[1] = -1;
	maq_atribuicao.est_atual = 0;
	maq_atribuicao.transicao_atual = 0;
}

void iniciaMaqOperando() {
	maq_operando.num_estados = 2;
	maq_operando.nome = "OPERANDO";
	
	criaTransicao(&maq_operando, TOK_NULL, &maq_numero, 0, 1);
	criaTransicao(&maq_operando, TOK_NULL, &maq_identificador, 0, 1);
	
	maq_operando.est_final[0] = 1;
	maq_operando.est_final[1] = -1;
	maq_operando.est_atual = 0;
	maq_operando.transicao_atual = 0;
	
}

void iniciaMaqExpressao() {
	maq_expressao.num_estados = 2;
	maq_expressao.nome = "EXPRESSAO";
	
	criaTransicao(&maq_expressao, TOK_NULL, &maq_exparitmetica, 0, 1);
	criaTransicao(&maq_expressao, TOK_NULL, &maq_caractere, 0, 1);
	criaTransicao(&maq_expressao, TOK_NULL, &maq_string, 0, 1);
	criaTransicao(&maq_expressao, TOK_NULL, &maq_expbool, 0, 1);
	
	maq_expressao.est_final[0] = 1;
	maq_expressao.est_final[1] = -1;
	maq_expressao.est_atual = 0;
	maq_expressao.transicao_atual = 0;
}

void iniciaMaqCaractere() {
	maq_caractere.num_estados = 2;
	maq_caractere.nome = "CARACTERE";
	
	criaTransicao(&maq_caractere, TOK_CHAR, NULL, 0, 1);
	
	maq_caractere.est_final[0] = 1;
	maq_caractere.est_final[1] = -1;
	maq_caractere.est_atual = 0;
	maq_caractere.transicao_atual = 0;
}

void iniciaMaqNumero() {
	maq_numero.num_estados = 2;
	maq_numero.nome = "NUMERO";
	
	criaTransicao(&maq_numero, TOK_NUM, NULL, 0, 1);
	
	maq_numero.est_final[0] = 1;
	maq_numero.est_final[1] = -1;
	maq_numero.est_atual = 0;
	maq_numero.transicao_atual = 0;
}

void iniciaMaqExparitmetica() {
	maq_exparitmetica.num_estados = 2;
	maq_exparitmetica.nome = "EXPARITMETICA";
	
	criaTransicao(&maq_exparitmetica, TOK_NULL, &maq_operando, 0, 1);
	criaTransicao(&maq_exparitmetica, TOK_NULL, &maq_operadorarit, 1, 0);
	
	maq_exparitmetica.est_final[0] = 1;
	maq_exparitmetica.est_final[1] = -1;
	maq_exparitmetica.est_atual = 0;
	maq_exparitmetica.transicao_atual = 0;
}

void iniciaMaqString() {
	maq_string.num_estados = 2;
	maq_string.nome = "STRING";
	
	criaTransicao(&maq_string, TOK_STRING, NULL, 0, 1);
	
	maq_string.est_final[0] = 1;
	maq_string.est_final[1] = -1;
	maq_string.est_atual = 0;
	maq_string.transicao_atual = 0;
}

void iniciaMaqOperadorarit() {
	maq_operadorarit.num_estados = 2;
	maq_operadorarit.nome = "OPERADORARIT";
	
	criaTransicao(&maq_operadorarit, TOK_MAIS, NULL, 0, 1);
	criaTransicao(&maq_operadorarit, TOK_MENOS, NULL, 0, 1);
	criaTransicao(&maq_operadorarit, TOK_VEZES, NULL, 0, 1);
	criaTransicao(&maq_operadorarit, TOK_DIVIDIDO, NULL, 0, 1);
	
	maq_operadorarit.est_final[0] = 1;
	maq_operadorarit.est_final[1] = -1;
	maq_operadorarit.est_atual = 0;
	maq_operadorarit.transicao_atual = 0;
}

void iniciaMaqOperadorlogico() {
	maq_operadorlogico.num_estados = 2;
	maq_operadorlogico.nome = "OPERADORLOGICO";
	
	criaTransicao(&maq_operadorlogico, TOK_LOG_IGUAL, NULL, 0, 1);
	criaTransicao(&maq_operadorlogico, TOK_LOG_MENOR_IGUAL, NULL, 0, 1);
	criaTransicao(&maq_operadorlogico, TOK_LOG_MAIOR_IGUAL, NULL, 0, 1);
	criaTransicao(&maq_operadorlogico, TOK_LOG_MENOR, NULL, 0, 1);
	criaTransicao(&maq_operadorlogico, TOK_LOG_MAIOR, NULL, 0, 1);
	criaTransicao(&maq_operadorlogico, TOK_LOG_DIFERENTE, NULL, 0, 1);
	
	maq_operadorlogico.est_final[0] = 1;
	maq_operadorlogico.est_final[1] = -1;
	maq_operadorlogico.est_atual = 0;
	maq_operadorlogico.transicao_atual = 0;
}

void iniciaMaqExpbool() {
	maq_expbool.num_estados = 2;
	maq_expbool.nome = "EXPBOOL";
	
	criaTransicao(&maq_expbool, TOK_VERDADEIRO, NULL, 0, 1);
	criaTransicao(&maq_expbool, TOK_FALSO, NULL, 0, 1);
	
	maq_expbool.est_final[0] = 1;
	maq_expbool.est_final[1] = -1;
	maq_expbool.est_atual = 0;
	maq_expbool.transicao_atual = 0;
}

void iniciaMaqCondicao() {
	maq_condicao.num_estados = 12;
	maq_condicao.nome = "CONDICAO";
	
	criaTransicao(&maq_condicao, TOK_SE, NULL, 0, 1);
	criaTransicao(&maq_condicao, TOK_PARENTESES_ABRE, NULL, 1, 2);
	criaTransicao(&maq_condicao, TOK_NULL, &maq_expcondicao, 2, 3);
	criaTransicao(&maq_condicao, TOK_PARENTESES_FECHA, NULL, 3, 4);
	criaTransicao(&maq_condicao, TOK_CHAVES_ABRE, NULL, 4, 5);
	criaTransicao(&maq_condicao, TOK_NULL, &maq_comandos, 5, 6);
	criaTransicao(&maq_condicao, TOK_CHAVES_FECHA, NULL, 6, 7);
	criaTransicao(&maq_condicao, TOK_SENAO, NULL, 7, 8);
	criaTransicao(&maq_condicao, TOK_PARENTESES_ABRE, NULL, 8, 9);
	criaTransicao(&maq_condicao, TOK_NULL, &maq_comandos, 9, 10);
	criaTransicao(&maq_condicao, TOK_CHAVES_FECHA, NULL, 10, 11);
	
	maq_condicao.est_final[0] = 7;
	maq_condicao.est_final[1] = 11;
	maq_condicao.est_atual = 0;
	maq_condicao.transicao_atual = 0;
}

void iniciaMaqExpcondicao() {
	maq_expcondicao.num_estados = 4;
	maq_expcondicao.nome = "EXPCONDICAO";
	
	criaTransicao(&maq_expcondicao, TOK_NULL, &maq_expressao, 0, 1);
	criaTransicao(&maq_expcondicao, TOK_NULL, &maq_operadorlogico, 1, 2);
	criaTransicao(&maq_expcondicao, TOK_NULL, &maq_expressao, 2, 3);
	criaTransicao(&maq_expcondicao, TOK_NULL, &maq_operadorcond, 3, 0);
	
	maq_expcondicao.est_final[0] = 3;
	maq_expcondicao.est_final[1] = -1;
	maq_expcondicao.est_atual = 0;
	maq_expcondicao.transicao_atual = 0;
}

void iniciaMaqOperadorcond() {
	maq_operadorcond.num_estados = 2;
	maq_operadorcond.nome = "OPERADORCOND";
	
	criaTransicao(&maq_operadorcond, TOK_LOG_E, NULL, 0, 1);
	criaTransicao(&maq_operadorcond, TOK_LOG_OU, NULL, 0, 1);
	
	maq_operadorcond.est_final[0] = 1;
	maq_operadorcond.est_final[1] = -1;
	maq_operadorcond.est_atual = 0;
	maq_operadorcond.transicao_atual = 0;
}

void iniciaMaqIteracao() {
	maq_iteracao.num_estados = 8;
	maq_iteracao.nome = "ITERACAO";
	
	criaTransicao(&maq_iteracao, TOK_ENQUANTO, NULL, 0, 1);
	criaTransicao(&maq_iteracao, TOK_PARENTESES_ABRE, NULL, 1, 2);
	criaTransicao(&maq_iteracao, TOK_NULL, &maq_expcondicao, 2, 3);
	criaTransicao(&maq_iteracao, TOK_PARENTESES_FECHA, NULL, 3, 4);
	criaTransicao(&maq_iteracao, TOK_CHAVES_ABRE, NULL, 4, 5);
	criaTransicao(&maq_iteracao, TOK_NULL, &maq_comandos, 5, 6);
	criaTransicao(&maq_iteracao, TOK_CHAVES_FECHA, NULL, 6, 7);
	
	maq_iteracao.est_final[0] = 7;
	maq_iteracao.est_final[1] = -1;
	maq_iteracao.est_atual = 0;
	maq_iteracao.transicao_atual = 0;
}

void iniciaMaqChamadafuncao() {
	maq_chamadafuncao.num_estados = 7;
	maq_chamadafuncao.nome = "CHAMADAFUNCAO";
	
	criaTransicao(&maq_chamadafuncao, TOK_NULL, &maq_identificador, 0, 1);
	criaTransicao(&maq_chamadafuncao, TOK_PARENTESES_ABRE, NULL, 1, 2);
	criaTransicao(&maq_chamadafuncao, TOK_NULL, &maq_identificador, 2, 3);
	criaTransicao(&maq_chamadafuncao, TOK_PARENTESES_FECHA, NULL, 2, 4);
	criaTransicao(&maq_chamadafuncao, TOK_VIRGULA, NULL, 3, 5);
	criaTransicao(&maq_chamadafuncao, TOK_PARENTESES_FECHA, NULL, 3, 4);
	criaTransicao(&maq_chamadafuncao, TOK_PONTO_VIRGULA, NULL, 4, 6);
	criaTransicao(&maq_chamadafuncao, TOK_NULL, &maq_identificador, 5, 3);
	
	maq_chamadafuncao.est_final[0] = 6;
	maq_chamadafuncao.est_final[1] = -1;
	maq_chamadafuncao.est_atual = 0;
	maq_chamadafuncao.transicao_atual = 0;
}

void iniciaMaqFuncao() {
	maq_funcao.num_estados = 10;
	maq_funcao.nome = "FUNCAO";
	
	criaTransicao(&maq_funcao, TOK_NULL, &maq_tipo, 0, 1);
	criaTransicao(&maq_funcao, TOK_FUNCAO, NULL, 1, 2);
	criaTransicao(&maq_funcao, TOK_NULL, &maq_identificador, 2, 3);
	criaTransicao(&maq_funcao, TOK_PARENTESES_ABRE, NULL, 3, 4);
	criaTransicao(&maq_funcao, TOK_NULL, &maq_argumentos, 4, 5);
	criaTransicao(&maq_funcao, TOK_PARENTESES_FECHA, NULL, 5, 6);
	criaTransicao(&maq_funcao, TOK_CHAVES_ABRE, NULL, 6, 7);
	criaTransicao(&maq_funcao, TOK_NULL, &maq_comandos, 7, 8);
	criaTransicao(&maq_funcao, TOK_NULL, &maq_retorno, 8, 9);
	criaTransicao(&maq_funcao, TOK_CHAVES_FECHA, NULL, 9, 10);
	
	maq_funcao.est_final[0] = 10;
	maq_funcao.est_final[1] = -1;
	maq_funcao.est_atual = 0;
	maq_funcao.transicao_atual = 0;
}

void iniciaMaqArgumentos() {
	maq_argumentos.num_estados = 3;
	maq_argumentos.nome = "ARGUMENTOS";
	
	criaTransicao(&maq_argumentos, TOK_NULL, &maq_tipo, 0, 1);
	criaTransicao(&maq_argumentos, TOK_NULL, &maq_identificador, 1, 2);
	criaTransicao(&maq_argumentos, TOK_VIRGULA, &maq_identificador, 2, 0);
	
	maq_argumentos.est_final[0] = 2;
	maq_argumentos.est_final[1] = -1;
	maq_argumentos.est_atual = 0;
	maq_argumentos.transicao_atual = 0;
}

void iniciaMaqRetorno() {
	maq_retorno.num_estados = 4;
	maq_retorno.nome = "RETORNO";
	
	criaTransicao(&maq_retorno, TOK_RETORNO, NULL, 0, 1);
	criaTransicao(&maq_retorno, TOK_NULL, &maq_identificador, 1, 2);
	criaTransicao(&maq_retorno, TOK_PONTO_VIRGULA, NULL, 1, 3);
	criaTransicao(&maq_retorno, TOK_PONTO_VIRGULA, NULL, 2, 3);
	
	maq_retorno.est_final[0] = 3;
	maq_retorno.est_final[1] = -1;
	maq_retorno.est_atual = 0;
	maq_retorno.transicao_atual = 0;
}

void iniciaMaqEntrada() {
	maq_entrada.num_estados = 4;
	maq_entrada.nome = "ENTRADA";
	
	criaTransicao(&maq_entrada, TOK_ENTRADA, NULL, 0, 1);
	criaTransicao(&maq_entrada, TOK_NULL, &maq_identificador, 1, 2);
	criaTransicao(&maq_entrada, TOK_PONTO_VIRGULA, NULL, 2, 3);
	
	maq_entrada.est_final[0] = 3;
	maq_entrada.est_final[1] = -1;
	maq_entrada.est_atual = 0;
	maq_entrada.transicao_atual = 0;
}

void iniciaMaqSaida() {
	maq_saida.num_estados = 4;
	maq_saida.nome = "SAIDA";
	
	criaTransicao(&maq_saida, TOK_SAIDA, NULL, 0, 1);
	criaTransicao(&maq_saida, TOK_NULL, &maq_identificador, 1, 2);
	criaTransicao(&maq_saida, TOK_PONTO_VIRGULA, NULL, 2, 3);
	
	maq_saida.est_final[0] = 3;
	maq_saida.est_final[1] = -1;
	maq_saida.est_atual = 0;
	maq_saida.transicao_atual = 0;
}

void criaTransicao(MaquinaEstados *maq, int tok_id, MaquinaEstados *maq_destino, int est_origem, int est_destino) {
	Transicao t;
	t.token_id = tok_id;
	t.maq_destino = maq_destino;
	t.est_origem = est_origem;
	t.est_destino = est_destino;
	maq->transicoes[maq->num_transicoes] = t;
	maq->num_transicoes++;
}

int classificaToken(Token* token) {
	if (token == NULL) return TOK_NULL;
	if (strcmp(token->type, "COMANDO") == 0) {
		if (strcmp(token->value, "prog") == 0) return TOK_PROG;
		if (strcmp(token->value, "int") == 0) return TOK_INT;
		if (strcmp(token->value, "char") == 0) return TOK_CHAR;
		if (strcmp(token->value, "string") == 0) return TOK_STRING;
		if (strcmp(token->value, "float") == 0) return TOK_FLOAT;
		if (strcmp(token->value, "bool") == 0) return TOK_BOOL;
		if (strcmp(token->value, "verdadeiro") == 0) return TOK_VERDADEIRO;
		if (strcmp(token->value, "falso") == 0) return TOK_FALSO;
		if (strcmp(token->value, "se") == 0) return TOK_SE;
		if (strcmp(token->value, "senao") == 0) return TOK_SENAO;
		
		if (strcmp(token->value, "enquanto") == 0) return TOK_ENQUANTO;
		if (strcmp(token->value, "funcao") == 0) return TOK_FUNCAO;
		
		if (strcmp(token->value, "retorna") == 0) return TOK_RETORNO;
		if (strcmp(token->value, "entrada") == 0) return TOK_ENTRADA;
		if (strcmp(token->value, "saida") == 0) return TOK_SAIDA;
	} else if (strcmp(token->type, "SIMBOLO") == 0) {
		if (strcmp(token->value, "{") == 0) return TOK_CHAVES_ABRE;
		if (strcmp(token->value, "}") == 0) return TOK_CHAVES_FECHA;
		if (strcmp(token->value, ";") == 0) return TOK_PONTO_VIRGULA;
		if (strcmp(token->value, "=") == 0) return TOK_IGUAL;
		if (strcmp(token->value, "'") == 0) return TOK_ASPAS_SIMPLES;
		if (strcmp(token->value, "\"") == 0) return TOK_ASPAS_DUPLAS;
		if (strcmp(token->value, "+") == 0) return TOK_MAIS;
		if (strcmp(token->value, "-") == 0) return TOK_MENOS;
		if (strcmp(token->value, "*") == 0) return TOK_VEZES;
		if (strcmp(token->value, "/") == 0) return TOK_DIVIDIDO;
		if (strcmp(token->value, "==") == 0) return TOK_LOG_IGUAL;
		if (strcmp(token->value, "<=") == 0) return TOK_LOG_MENOR_IGUAL;
		if (strcmp(token->value, ">=") == 0) return TOK_LOG_MAIOR_IGUAL;
		if (strcmp(token->value, "<") == 0) return TOK_LOG_MENOR;
		if (strcmp(token->value, ">") == 0) return TOK_LOG_MAIOR;
		if (strcmp(token->value, "!=") == 0) return TOK_LOG_DIFERENTE;
		if (strcmp(token->value, "(") == 0) return TOK_PARENTESES_ABRE;
		if (strcmp(token->value, ")") == 0) return TOK_PARENTESES_FECHA;
		if (strcmp(token->value, "&&") == 0) return TOK_LOG_E;
		if (strcmp(token->value, "||") == 0) return TOK_LOG_OU;
		if (strcmp(token->value, ",") == 0) return TOK_VIRGULA;
	} else if (strcmp(token->type, "IDENTIFICADOR") == 0) {
		return TOK_ID;
	} else if (strcmp(token->type, "NUMERO") == 0) return TOK_NUM;
	return TOK_NULL;
}

void semantico_tbd() {
	printf("TODO\n");
}