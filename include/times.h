#ifndef TIMES_H
#define TIMES_H

#define MAX_LINHAS 50
#define MAX_TEXTO 128

//
//estrutura principal
typedef struct {
    char time[MAX_TEXTO];
    char pais[MAX_TEXTO];
    char jogador[MAX_TEXTO];
    char destaque[MAX_TEXTO];
    char dica[MAX_TEXTO];
} TimesCSV;

// Protótipos das funções
void listar(TimesCSV *times, int count);
void pesquisar(TimesCSV *times, int count);
void editar(TimesCSV *times, int count);
void excluir(TimesCSV *times, int *count);
TimesCSV* inserir(TimesCSV *times, int *count, int *capacidade);

#endif