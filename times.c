#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "times.h"

void listar(TimesCSV *times, int count) {
    printf("\n=== LISTA DE TIMES ===\n");
    for (int i = 0; i < count; i++) {
        printf("%d - %s | %s | %s | %s | %s\n",
            i,
            times[i].time,
            times[i].pais,
            times[i].jogador,
            times[i].destaque,
            times[i].dica
        );
    }
}




void pesquisar(TimesCSV *times, int count) {
    setbuf(stdin,NULL);
    char busca[MAX_TEXTO];
    printf("Digite o nome do time: ");
    fgets(busca, MAX_TEXTO, stdin);
    busca[strcspn(busca, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcasecmp(times[i].time, busca) == 0) {
            printf("Encontrado: %s | %s | %s | %s | %s\n",
                times[i].time, times[i].pais, times[i].jogador,
                times[i].destaque, times[i].dica
            );
            return;
        }
    }

    printf("Time não encontrado!\n");
}

void editar(TimesCSV *times, int count) {
    int id;
    listar(times, count);
    printf("\nDigite o ID para editar: ");
    scanf("%d", &id);
    getchar();
    
    if (id < 0 || id >= count) {
        printf("ID inválido!\n");
        return;
    }

    printf("Novo nome do time: ");
    fgets(times[id].time, MAX_TEXTO, stdin);
    times[id].time[strcspn(times[id].time,"\n")] = 0;
    
    printf("Atualizado com sucesso!\n");
}

void excluir(TimesCSV *times, int *count) {
    int id;
    listar(times, *count);
    printf("\nDigite o ID para excluir: ");
    scanf("%d", &id);
    getchar();

    if (id < 0 || id >= *count) {
        printf("ID inválido!\n");
        return;
    }

    for (int i = id; i < *count - 1; i++) {
        times[i] = times[i + 1];
    }

    (*count)--;

    printf("Registro removido!\n");
}

TimesCSV* inserir(TimesCSV *times, int *count, int *capacidade) {
    if (*count >= *capacidade) {
        *capacidade *= 2;
        TimesCSV *temp = realloc(times, sizeof(TimesCSV) * (*capacidade));
        if (!temp) {
            perror("Erro ao realocar memória");
            exit(1);
        }
        times = temp;
    }


    
    printf("Nome do time: ");
    fgets(times[*count].time, MAX_TEXTO, stdin);
    times[*count].time[strcspn(times[*count].time,"\n")] = 0;
    
    printf("Pais: ");
    fgets(times[*count].pais, MAX_TEXTO, stdin);
    times[*count].pais[strcspn(times[*count].pais,"\n")] = 0;
    
    printf("Jogador: ");
    fgets(times[*count].jogador, MAX_TEXTO, stdin);
    times[*count].jogador[strcspn(times[*count].jogador,"\n")] = 0;

    printf("Destaque: ");
    fgets(times[*count].destaque, MAX_TEXTO, stdin);
    times[*count].destaque[strcspn(times[*count].destaque,"\n")] = 0;
    
    printf("Dica: ");
    fgets(times[*count].dica, MAX_TEXTO, stdin);
    times[*count].dica[strcspn(times[*count].dica,"\n")] = 0;

    (*count)++;
    printf("Registro inserido!\n");
    
    (*count)++;
    printf("Registro inserido!\n");

    return times;
    }

