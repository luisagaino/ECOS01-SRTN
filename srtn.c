#include <stdio.h>

struct Processos {
    int criacao;    // data de criação
    int duracao;    // duração em segundos
    int prioridade; // prioridade estática (não importa para o srtn)
};



int main() {
    FILE *entrada, *saida;                  // arquivos de entrada e saida
    struct Processo p[10];                  // teremos até 10 processos nessa simulação
    
    entrada = fopen("in.txt", "r");         // abre arquivo de entrada para ler os dados
    if(entrada == NULL) {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }
    
    for(int i = 0; i < n) {
        
    }
    
    saida = fopen("out.txt", "w");          // abre arquivo de saída para escrever os resultados

    fprintf(saida, "teste");                // escreve no arquivo de saída

    fclose(entrada);                        // não precisa mais do arquivo de entrada
    fclose(saida);                          // não precisa mais do arquivo de saída
    return 0;
}
