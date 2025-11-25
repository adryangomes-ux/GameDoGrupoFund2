#ifndef TIMES_H
#define TIMES_H

#define MAX_LINHAS 50
#define MAX_COLUNAS 25
#define MAX_TEXTO 128

// cores ANSII
#define VERMELHO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define AZUL    "\x1b[34m"
#define CIANO   "\x1b[36m"
#define RESET   "\x1b[0m"


typedef struct {
    char time[MAX_TEXTO];
    char pais[MAX_TEXTO];
    char jogador[MAX_TEXTO];
    char destaque[MAX_TEXTO];
    char dica[MAX_TEXTO];
} TimesCSV;

// Protótipos das funções
void listar(TimesCSV times[], int count);
void inserir(TimesCSV times[], int *count);
void pesquisar(TimesCSV times[], int count);
void editar(TimesCSV times[], int count);
void excluir(TimesCSV times[], int *count);

#endif