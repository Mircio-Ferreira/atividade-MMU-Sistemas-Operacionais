#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LEN 5

int main(){
    int array[LEN] ={-1,-1,-1,-1,-1}; 
    int tempo[LEN] ={0};                  
    int contadorTempo= 0;

    srand(time(NULL));
    int lotado = 0;

    for(int i = 0; i < 20; i++){
        int numRandom = rand() % 10;
        contadorTempo++;
        int tem = 0;
        for(int j = 0; j < LEN; j++) {
            if(array[j] == numRandom){
                tem = 1;
                tempo[j] = contadorTempo;
                break;
            }
        }

        if(tem){
            printf("Numero %d ja existe.\n", numRandom);
        } else {            // ainda tem espaço vazio
            if(lotado < LEN){
                for(int k = 0; k < LEN; k++) {
                    if(array[k] == -1){
                        array[k] = numRandom;
                        tempo[k] = contadorTempo;
                        lotado++;
                        break;
                    }
                }
            } else {
                int menorTempo = tempo[0]; // precisa substituir o menos recentemente usado (menor tempo)
                int indiceLRU = 0;
                for(int k = 1; k < LEN; k++){
                    if(tempo[k] < menorTempo){
                        menorTempo = tempo[k];
                        indiceLRU = k;
                    }
                }
                array[indiceLRU] = numRandom;
                tempo[indiceLRU] = contadorTempo;
            }
        }
        printf("Processo sorteado: %d      ", numRandom);
        for(int k = 0; k < LEN; k++) printf("|%d|", array[k]);
        printf("\n");
    }

    return 0;
}
