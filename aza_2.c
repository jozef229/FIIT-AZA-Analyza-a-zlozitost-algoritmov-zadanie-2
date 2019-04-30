//
//  main.c
//  AZA-2
//
//  Created by Jozef Varga on 24.4.18.
//  Copyright © 2018 Jozef Varga. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Plength=1000000;
char P[1000001];
int n;
int vstup;
int FR, FPocet;
int aktualny_pociatok;
int pokus;
int spravne = 0;


void generateP(){
    P[0]='a';
    long read=0,write=1;
    while(Plength>write) {
        if (read % 39 ==38) read++;
        char r=P[read++];
        if (r=='a') {P[write++]='b';P[write++]='a';P[write++]='a';}
        else if (r=='b') {P[write++]='a';P[write++]='c';}
        else if (r=='c') {P[write++]='b';};
    }
    P[Plength]=0;
}

void prechod(int x, int y, char *R){
    //printf("%c %c\n",P[x], R[y]);
    if(x==n || y==vstup){
        if(y==vstup && spravne == 0 && ((FPocet == -1)||(pokus < FPocet))){
            
            FR = aktualny_pociatok;
            FPocet = pokus;
            //printf("%d %d \n",FR, FPocet);
            return;
        }
        else {
            spravne = 1;
            return;
        }
    }
    if(x+2<=n && y+3 <= vstup && P[x] == 'a' && P[x+1] == 'a' && R[y] == 'a' && R[y+1] == 'a' && R[y+2] == 'a'){
        pokus ++;
        if(pokus <= FPocet){
            return;
        }
        prechod(x+2, y+3, R);
        pokus--;
        spravne = 0;
        
    }if(x+4<=n && y+5 <= vstup && P[x] == 'a' && P[x+1] == 'b' && P[x+2] == 'a' && P[x+3] == 'c' && R[y] == 'a' && R[y+1] == 'b' && R[y+2] == 'a' && R[y + 3] == 'a' && R[y+4] == 'c'){
        pokus ++;
        if(pokus <= FPocet)return;
        prechod(x+4, y+5, R);
        pokus--;
        spravne = 0;
        
    }if(x+9<=n && y+1 <= vstup  && P[x] == 'b' && P[x+1] == 'a' && P[x+2] == 'a' && P[x+3] == 'b' && P[x +4] == 'a' && P[x+5] == 'a' && P[x+6] == 'b' && P[x+7] == 'a' && P[x+8] == 'a' && R[y] == 'a'){
        pokus ++;
        if(pokus <= FPocet)return;
        prechod(x+9, y+1, R);
        pokus--;
        spravne = 0;
    }if(P[x] == R[y]){
        prechod(x+1, y+1, R);
        spravne = 0;
    }else{
        spravne = 1;
        return;
    }
}

int main(int argc, const char * argv[]) {
    generateP();
    n=0;
    int pocet;
    scanf("%d",&pocet);
    for(int i=0;i<pocet;i++){
        FR = -1;
        FPocet = -1;
        pokus = 0;
        char *R = (char *)malloc(10000 * sizeof(char));;
        scanf("%d",&n);
        scanf("%s",R);
        vstup = strlen(R);
            for(int x=0;x<n;x++){
                spravne = 0;
                aktualny_pociatok = x;
                prechod(x, 0, R);
                if(FPocet == 0)break;
            }
        if(FR == -1)printf("No solution.\n");
        else printf("%d,%d\n",FR, FPocet);
    }
    return 0;
}