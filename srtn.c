#include <stdio.h>

struct Processos {
    int criacao;    // data de criação
    int duracao;    // duração em segundos
    int prioridade; // prioridade estática
};



int main() {
    FILE *entrada, *saida;                  // arquivos de entrada e saida

    entrada = fopen("arquivo.txt", "r");    // abre arquivo de entrada para ler os dados

    saida = fopen("saida", "w");            // abre arquivo de saida para escrever os resultados

    fprintf(saida, "teste");                // escreve no arquivo de saida

    fclose(entrada);                        // fecha arquivo
    fclose(saida);                          // fecha arquivo
    return 0;
}