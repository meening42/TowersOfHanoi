#include <stdio.h>
#include <stdlib.h>

#define POLES 3
#define MAX_DISCS 15

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
//
// EXAMPLE 2:
//                            |       |       |
//      {[4,3,0,0...]         |       |       |
// a =   [0,0,0,0...]   =  ###|       |      #|
//       [2,1,0,0...]}    ####|       |     ##|
//                       pole0   pole1    pole2
//
//
//
// src = source
// dst = destination
// spr = spare
//******************************************
int discs;      //number of all discs

void moveDisc(int, int, int[POLES][MAX_DISCS]);
void initPoles(int, int[POLES][MAX_DISCS]);
int getUserInput();
void printOutTowers(int[POLES][MAX_DISCS]);
void printOutArray(int[POLES][MAX_DISCS]);
void solveHanoi(int, int, int, int, int[POLES][MAX_DISCS]);


int main()
{
    int a[POLES][MAX_DISCS];
    discs = getUserInput();
    initPoles(discs, a);
    printf("Lets move this stuff!\n");
    solveHanoi(discs,0,2,1,a);

    return 0;
}

//******************************************
int getUserInput(){
    int n = 0;
    printf("Input the number of discs on a tower: ");
    scanf("%d",&n);
    if(n<1){
        n = 1;
    }
    if(n>15){
        n = 15;
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
            for(int j = 0; j<discs; j++){
                if (j>=discs-a[i][row]){
                    printf("#");
                }
                else  printf(" ");
            }
            printf("|");
        }
        printf("\n");
    }
    printf("\n");
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




