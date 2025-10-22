#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define LEN 5

int main(){
    int array[LEN]={ -1, -1, -1, -1, -1 };


    srand(time(NULL));
    int lotado=0;
    int last=0;

    for(int i=0;i<20;i++){
        int numRandom=rand()%10;
        int tem=0;
        for(int j=0;j<LEN;j++) {
            if(array[j]==numRandom) tem=1;
        }
        if(tem) continue;
        if(lotado!=LEN){
            for(int k=0;k<LEN;k++) {
            if(array[k]==-1){
                array[k] = numRandom;
                lotado++;
                break;
            }
        }
        }
        else array[last++%LEN]=numRandom;
        
        printf("Numero sorteado: %d      ",numRandom);
        for(int k=0;k<LEN;k++)printf("|%d|",array[k]);
        printf("\n");
    }
    
    return 0;
}