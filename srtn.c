#include <stdio.h>
#include <stdlib.h>

struct processo {
    int criacao;    // data de criação
    int duracao;    // duração em segundos
    int prioridade; // prioridade estática (não importa para o srtn)
    int vida;       // tempo médio de vida
    int espera;     // tempo médio de espera
};

int escolheProcesso(int n, int tempo, struct processo p[10], int finalizados[10], int tempoRestante[10]);
void imprimeDiagrama(FILE *saida, int tempo, int atual, int n);

int main() {
    FILE *entrada, *saida;                          // arquivos de entrada e saida
    struct processo p[10];                          // teremos até 10 processos nessa simulação
    int trocas = 0;                                 // número de trocas de contexto
    int completos = 0;                              // quantidade de processos completos
    int tempo = 0;                                  // contador de tempo

    entrada = fopen("in.txt", "r");                 // abre arquivo de entrada para ler os dados
    if(entrada == NULL) {
        printf("Erro ao abrir arquivo!");
        exit(1);
    } 

    int n = 0;                                      // para contar o número de processos dentro do arquivo
    int finalizados[10];                            // marca quais processos foram finalizados
    int tempoRestante[10];                          // marca quanto tempo falta para finalizar um processo
    for(int i = 0; i < 10; i++) {                   // salva as informações dos processos em um vetor
        fscanf(entrada, "%d", &p[i].criacao);
        fscanf(entrada, "%d", &p[i].duracao);
        fscanf(entrada, "%d", &p[i].prioridade);
        n++;                                        // contador de processos
        finalizados[i] = 0;
        tempoRestante[i] = p[i].duracao;
        if(feof(entrada)) break;                    // se chegar ao final do arquivo sai do loop
    }
    fclose(entrada);                                // não precisa mais do arquivo de entrada 
    
    saida = fopen("out.txt", "w");                  // abre arquivo de saída para escrever os resultados
    fprintf(saida, "tempo   ");
    for(int i = 0; i < n; i++) {
        fprintf(saida, "P%d  ", i+1);
    }
    fprintf(saida, "\n");

    //while(completos != n) {                         // enquanto ainda há processos que não foram completados
        int atual = escolheProcesso(n, tempo, p, finalizados, tempoRestante);
        imprimeDiagrama(saida, tempo, atual, n);
        /*COMPLETAR*/
    //}

    // escrevendo no arquivo de saída
    fprintf(saida, "\n|    | Tempo de vida | Tempo de espera |\n");
    for(int i = 0; i < n; i++) {
        fprintf(saida, "| P%d |       %d       |        %d        |\n", i, p[i].vida, p[i].espera);
    }
    fprintf(saida, "\nNúmero de trocas de contexto: %d\n\n", trocas);
    fclose(saida);                                  // não precisa mais do arquivo de saída
    
    return 0;
}

// para escolher o processo que será executado
int escolheProcesso(int n, int tempo, struct processo p[10], int finalizados[10], int tempoRestante[10]) {                      
    int atual = -1, tmp = 9999;
        for(int i = 0; i < n; i++) {
            // se o processo já foi criado mas ainda não foi finalizado
            if((p[i].criacao <= tempo) && (finalizados[i] == 0)) {
                // se a duração desse processo é a menor então esse é o processo atual
                if(tempoRestante[i] < tmp) {
                    tmp = tempoRestante[i];
                    atual = i;
                }
                // se há dois processos com a mesma duração
                if(tempoRestante[i] == tmp) {
                    // o processo criado primeiro será o processo atual
                    if(p[i].criacao < p[atual].criacao) {
                        tmp = tempoRestante[i];
                        atual = i;
                    }
                }
            }
        }

    return atual;
}

void imprimeDiagrama(FILE *saida, int tempo, int atual, int n) {
    if(tempo < 10) {
        if(tempo + 1 < 10) {
            fprintf(saida, " %d- %d   ", tempo, tempo+1);
        } else {
            fprintf(saida, " %d-%d   ", tempo, tempo+1);
        }
    } else {
        fprintf(saida, "%d-%d   ", tempo, tempo+1);
    }

    for(int i=0; i<n; i++) {
        if(atual == i) {
            fprintf(saida, "##  ");
        } else {
            fprintf(saida, "--  ");
        }
    }
    fprintf(saida, "\n");
}