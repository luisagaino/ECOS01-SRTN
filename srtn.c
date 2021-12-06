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
void imprimeDiagrama(FILE *saida, int tempo, int atual, int n, struct processo p[10], int finalizados[10]);

int main() {
    FILE *entrada, *saida;                          // arquivos de entrada e saida
    struct processo p[10];                          // teremos até 10 processos nessa simulação
    int trocas = 0;                                 // número de trocas de contexto
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
    for(int i = 0; i < n; i++) fprintf(saida, "P%d  ", i+1);
    fprintf(saida, "\n");

    int atual = -1, anterior = -1;                  // guarda o processo atual e o anterior
    int completos = 0;                              // contador de processos completos
    while(completos != n) {                         // enquanto ainda há processos que não foram completados
        atual = escolheProcesso(n, tempo, p, finalizados, tempoRestante);
        imprimeDiagrama(saida, tempo, atual, n, p, finalizados);
        
        if(atual != anterior) trocas++;             // se o processo anterior é diferente do atual é porque teve troca de contexto

        if(atual != -1) {                           // se há um processo em execução
            tempoRestante[atual]--;                 // diminui o tempo restante do processo atual
            tempo++;                                // aumenta o contador de tempo
            if(tempoRestante[atual] == 0) {         // se o processo foi finalizado
                // tempo de vida = tempo atual - data de criação 
                p[atual].vida = tempo - p[atual].criacao;
                // tempo de espera = tempo de vida - tempo de duração
                p[atual].espera = p[atual].vida - p[atual].duracao;
                finalizados[atual] = 1;             // adiciona na lista de finalizados
                completos++;
            }
        } else tempo++;                             // aumenta o contador de tempo

        anterior = atual;
    }
    
    // imprime as informações de tempo de vida, tempo de espera e número de trocas de contexto
    fprintf(saida, "\n|    | Tempo de vida | Tempo de espera |\n");
    for(int i = 0; i < n; i++) {
        if(p[i].vida > 10) {
            if(p[i].espera > 10)
                fprintf(saida, "| P%d |       %d      |        %d       |\n", i+1, p[i].vida, p[i].espera);
            else
                fprintf(saida, "| P%d |       %d      |        %d        |\n", i+1, p[i].vida, p[i].espera);
        } else
            fprintf(saida, "| P%d |       %d       |        %d        |\n", i+1, p[i].vida, p[i].espera);
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

// imprime o diagrama de tempo de execução
void imprimeDiagrama(FILE *saida, int tempo, int atual, int n, struct processo p[10], int finalizados[10]) {
    if(tempo < 10) {
        if(tempo + 1 < 10)
            fprintf(saida, " %d- %d   ", tempo, tempo+1);
        else
            fprintf(saida, " %d-%d   ", tempo, tempo+1);
    } else
        fprintf(saida, "%d-%d   ", tempo, tempo+1);

    for(int i = 0; i < n; i++) {
        if(atual == i)
            fprintf(saida, "##  ");
        else
            if((p[i].criacao <= tempo) && (finalizados[i] == 0))
                fprintf(saida, "--  ");
            else
                fprintf(saida, "    ");
    }
    fprintf(saida, "\n");
}
