#include <stdio.h>
#include <stdlib.h>

struct processo {
    int criacao;    // data de criação
    int duracao;    // duração em segundos
    int prioridade; // prioridade estática (não importa para o srtn)
};

int main() {
    FILE *entrada, *saida;                          // arquivos de entrada e saida
    struct processo p[10];                          // teremos até 10 processos nessa simulação 
    int n = 0;                                      // para contar o número de processos dentro do arquivo

    entrada = fopen("in.txt", "r");                 // abre arquivo de entrada para ler os dados
    if(entrada == NULL) {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }
    
    for(int i = 0; i < 10; i++) {                   // salva as informações dos processos em um vetor
        fscanf(entrada, "%d", &p[i].criacao);
        fscanf(entrada, "%d", &p[i].duracao);
        fscanf(entrada, "%d", &p[i].prioridade);
        n++;                                        // contador de processos
        if(feof(entrada)) break;                    // se chegar ao final do arquivo sai do loop
    }

    for(int i = 0; i < n; i++) {
        printf("%d ", p[i].criacao);
        printf("%d ", p[i].duracao);
        printf("%d\n", p[i].prioridade);
    }
    
    //saida = fopen("out.txt", "w");                // abre arquivo de saída para escrever os resultados

    //fprintf(saida, "teste");                      // escreve no arquivo de saída

    fclose(entrada);                                // não precisa mais do arquivo de entrada
    //fclose(saida);                                // não precisa mais do arquivo de saída
    return 0;
}