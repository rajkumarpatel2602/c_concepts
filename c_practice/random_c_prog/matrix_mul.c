#include <stdio.h>

//Change values here to do multiplication.
#define r1 2
#define c1 2
#define r2 2
#define c2 2

int matA[r1][c1]={0};
int matB[r2][c2]={0};
int matR[r1][c2]={0};

void print_mat(int row, int col, int (*a)[col]){
    int i, j;
    printf ("\nMatrix : \n");
    for(i =0 ; i<row; i++){
        printf("\n");
        for(j=0; j<col; j++){
            printf("%d ", a[i][j]);
        }
    }
    printf("\n");
}

void mul_arr(int row, int m, int col, int (*a)[m], int (*b)[c2]){
    int res_r=row, res_c=col;
    int i, j, k;
    for(i=0; i<res_r; i++){
        for(j=0; j<res_c; j++){
            for(k=0; k<m; k++){
                matR[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    print_mat(r1, c2, matR);
}


void populate_arr(int row, int col, int (*arr)[col]){
    int i, j;
    for(i =0 ; i<row; i++){
        for(j=0; j<col; j++){
            printf("\nEnter element : ");
            int data = 0;
            scanf("%d", &data);
            arr[i][j] = data;
        }
    }
}

int main(){
    printf ("enter the elements for first matrix!\n");
    populate_arr(r1, c1, matA);
    printf ("enter the elements for second matrix!\n");
    populate_arr(r2, c2, matB);
    print_mat(r1, c1, matA);
    print_mat(r2, c2, matB);

    mul_arr(r1, r2, c2, matA, matB);
}
