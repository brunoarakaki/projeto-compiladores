//
//  analisador_sintatico.h
//  Compiladores
//
//  Created by Mayer Levy on 11/13/17.
//  Copyright © 2017 Mayer Levy. All rights reserved.
//

#ifndef analisador_sintatico_h
#define analisador_sintatico_h

#define TOK_NULL 0
#define TOK_PROG 1
#define TOK_CHAVES_ABRE 2
#define TOK_CHAVES_FECHA 3
#define TOK_INT 4
#define TOK_CHAR 5
#define TOK_STRING 6
#define TOK_FLOAT 7
#define TOK_BOOL 8
#define TOK_PONTO_VIRGULA 9
#define TOK_IGUAL 10
#define TOK_ASPAS_SIMPLES 11
#define TOK_ASPAS_DUPLAS 12
#define TOK_MAIS 13
#define TOK_MENOS 14
#define TOK_VEZES 15
#define TOK_DIVIDIDO 16
#define TOK_LOG_IGUAL 17
#define TOK_LOG_MENOR_IGUAL 18
#define TOK_LOG_MAIOR_IGUAL 19
#define TOK_LOG_MENOR 20
#define TOK_LOG_MAIOR 21
#define TOK_LOG_DIFERENTE 22
#define TOK_VERDADEIRO 23
#define TOK_FALSO 24
#define TOK_SE 25
#define TOK_PARENTESES_ABRE 26
#define TOK_PARENTESES_FECHA 27
#define TOK_SENAO 28
#define TOK_LOG_E 29
#define TOK_LOG_OU 30
#define TOK_ENQUANTO 31
#define TOK_FUNCAO 32
#define TOK_VIRGULA 33
#define TOK_RETORNO 34
#define TOK_ENTRADA 35
#define TOK_SAIDA 36
#define TOK_ID 37
#define TOK_NUM 38
#define TOK_END_CHAR 39

typedef struct transicao {
	int token_id;
	struct maquinaEstados *maq_destino;
	int est_origem;
	int est_destino;
} Transicao;

typedef struct maquinaEstados {
	char *nome;
	int num_estados;
	int num_transicoes;
	int est_final[2];
	int est_atual;
	int est_prox;
	int transicao_atual;
	Transicao transicoes[256];
} MaquinaEstados;

int executaMaquina(MaquinaEstados* maq, ListaToken *pilhaTokens);
void semantico_tbd();

void iniciaMaqProg();
void iniciaMaqDeclaracoes();
void iniciaMaqDeclaracao();
void iniciaMaqTipo();
void iniciaMaqComandos();
void iniciaMaqComando();
void iniciaMaqIdentificador();
void iniciaMaqAtribuicao();
void iniciaMaqOperando();
void iniciaMaqExpressao();
void iniciaMaqCaractere();
void iniciaMaqNumero();
void iniciaMaqExparitmetica();
void iniciaMaqString();
void iniciaMaqOperadorarit();
void iniciaMaqOperadorlogico();
void iniciaMaqExpbool();
void iniciaMaqCondicao();
void iniciaMaqExpcondicao();
void iniciaMaqOperadorcond();
void iniciaMaqIteracao();
void iniciaMaqChamadafuncao();
void iniciaMaqFuncao();
void iniciaMaqArgumentos();
void iniciaMaqRetorno();
void iniciaMaqEntrada();
void iniciaMaqSaida();

void iniciaMaquinas();

void criaTransicao(MaquinaEstados *maq, int tok_id, MaquinaEstados *maq_destino, int est_origem, int est_destino);

int classificaToken(Token *token);

void analiseSintatica(ListaToken *tokens);

#endif /* analisador_sintatico_h */
