#include "exportar.h"

void ExportarCSV(TimesCSV *times, int quantidade){
    FILE *arq = fopen("arquivos/TimesExportados.csv", "w");
    if (!arq) {
        printf("Erro ao criar o arquivo CSV!\n");
        return;
    }

    // Cabeçalho do CSV
    fprintf(arq, "Time,Pais,Jogador,Destaque,Dica\n");

    // Linhas de dados
    for (int i = 0; i < quantidade; i++)
    {
        fprintf(arq, "%s,%s,%s,%s,%s\n",
            times[i].time,
            times[i].pais,
            times[i].jogador,
            times[i].destaque,
            times[i].dica
        );
    }

    fclose(arq);
    printf("Arquivo CSV gerado com sucesso!\n");
}
