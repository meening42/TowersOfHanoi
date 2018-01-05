#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define POLES 3
#define MAX_DISCS 10

//******************************************
// a is a field showing position of discs
//   (of a size) on poles
//
// EXAMPLE 1:
//                          #|       |       |
//     {[4,3,2,1...]       ##|       |       |
// a =  [0,0,0,0...]  =   ###|       |       |
//      [0,0,0,0...]}    ####|       |       |
//                       pole0   pole1    pole2
//
// EXAMPLE 2:
//                            |       |       |
//      {[4,3,0,0...]         |       |       |
// a =   [0,0,0,0...]   =  ###|       |      #|
//       [2,1,0,0...]}    ####|       |     ##|
//                       pole0   pole1    pole2
//
//******************************************
int discs;      //number of all discs
FILE *f;


void  moveDisc(int, int, int[POLES][MAX_DISCS]);
void  initPoles(int, int[POLES][MAX_DISCS]);
int   getUserInput();
void  printOutTowers(int[POLES][MAX_DISCS]);
void  printOutArray(int[POLES][MAX_DISCS]);
void  solveHanoi(int, int, int, int, int[POLES][MAX_DISCS]);
char* getFileName(int n);
void  playSteps();
void  sleep(unsigned long);


int main()
{

    int a[POLES][MAX_DISCS];
    discs = getUserInput();

    f = fopen(getFileName(discs),"w");


    initPoles(discs, a);
    printf("Lets move this stuff!\n");
    solveHanoi(discs,0,2,1,a);
    fclose(f);

    playSteps();
    return 0;
}


//******************************************
// PSEUDO CODE (WIKI)
//A = [5, 4, 3, 2, 1]
//B = []
//C = []
//
//def move(n, source, target, auxiliary):
//    if n > 0:
//        # move n - 1 disks from source to auxiliary, so they are out of the way
//        move(n - 1, source, auxiliary, target)
//
//        # move the nth disk from source to target
//        target.append(source.pop())
//
//        # Display our progress
//        print(A, B, C, '##############', sep = '\n')
//
//        # move the n - 1 disks that we left on auxiliary onto target
//        move(n - 1, auxiliary, target, source)
//
// src = source
// dst = destination
// spr = spare
//******************************************
void solveHanoi(int n, int src, int dst, int spr, int a[POLES][MAX_DISCS]){
    if(dst == 2 && src == 0) spr = 1;
    if(dst == 1 && src == 2) spr = 0;
    if(dst == 0 && src == 1) spr = 2;
    if (n>0){
            solveHanoi(n-1, src, spr, dst, a);
            moveDisc(src,dst,a);
            printOutTowers(a);
            solveHanoi(n-1,spr,dst,src,a);
    }
}
//******************************************
int getUserInput(){
    int n = 0;
    printf("Input the number of discs on a tower: ");
    scanf("%d",&n);
    if(n<1){
        n = 1;
    }
    if(n>MAX_DISCS){
        n = MAX_DISCS;
    }
    return n;
}
//******************************************
void initPoles(int discNum, int a[POLES][MAX_DISCS]){
    int d = discNum;
    for(int i = 0; i < POLES; i++){
        for(int j = 0; j < discNum;j++){
            if (i == 0 && d>0){
                a[i][j] = d;
                d--;
            }
            else{
                a[i][j] = 0;
            }
        }
    }
    printOutTowers(a);

}
//******************************************
void printOutTowers(int a[POLES][MAX_DISCS]){
    int d = discs;
    for(int row = discs-1; row >=0; row--){
        for(int i = 0; i < POLES; i++){
            printf("  ");
            fprintf(f,"  ");
            for(int j = 0; j<discs; j++){
                if (j>=discs-a[i][row]){
                    printf("#");
                    fprintf(f,"#");
                }
                else {
                    printf(" ");
                    fprintf(f," ");
                }
            }
            printf("|");
            fprintf(f,"|");
        }
        printf("\n");
        fprintf(f,"\n");
    }
    // underline
    printf("  ");
    fprintf(f,"  ");
    for(int i=0;i<(3*discs+10); i++){
        printf("¯");
        fprintf(f,"¯");
    }
    printf("\n");
    fprintf(f,"\n\n");
}

//******************************************
void moveDisc(int src, int dst, int a[POLES][MAX_DISCS]){
    int d;
    for(int i=discs-1; i>=0;i--){
        if (a[src][i]>0){
            d = a[src][i];
            a[src][i]=0;
            break;
        }
    }

    for(int i=discs-1; i>=0;i--){
        if(a[dst][i]>0){
            a[dst][i+1]=d;
            break;
        }
        else if (i == 0){
            a[dst][0] = d;
        }
    }
}
//******************************************
void printOutArray(int a[POLES][MAX_DISCS]){
    for(int i = 0; i<POLES;i++){
        for(int j = 0;j<discs;j++){
            printf("%d, ", a[i][j]);
        }
        printf("\n");
    }
}


//******************************************
char* getFileName(int n){
    char static fileName[20];
    char snum[5];
    strcpy(fileName, "TowersOfHanoi");
    snprintf(snum,10,"%d",n);
    strcat(fileName,snum);
    return fileName;
}

//******************************************
void playSteps(){
    int n = discs +2;
    f = fopen(getFileName(discs),"r");
    char* line=NULL;
    ssize_t read;
    size_t len = 0;

    if (f == NULL)
        exit(EXIT_FAILURE);
    int i = 0;
    system("clear");
    while((read = getline(&line, &len, f)) != -1) {
        i++;
        printf("%s",line);
        if (i >= n){
            i=0;
            sleep(400000);
            system("clear");
        }
    }
}

//******************************************
void sleep(unsigned long mill)
{
	clock_t start = clock();
	while(clock() - start < mill) { }
}

