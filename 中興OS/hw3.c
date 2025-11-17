#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int rA, cA, rB, cB;
int **A, **B, **result;
void *MatrixMulti(void *arg) {
    int i = *((int *)arg);
    free(arg);
    for(int j=0; j<cB; j++) {
        int sum = 0;
        for(int k=0; k<cA; k++) {
            sum += A[i][k] * B[k][j];
        }
        result[i][j] = sum;
    }
    pthread_exit(0);
}
int main() {
    printf("Enter rows and columns for Matrix A:");
    scanf("%d%d", &rA, &cA);
    printf("Enter rows and columns for Matrix B:");
    scanf("%d%d", &rB, &cB);
    A = (int**)malloc(rA * sizeof(int *));
    for(int i=0; i<rA; i++) {
        A[i] = (int*)malloc(cA * sizeof(int));
    }
    B = (int**)malloc(rB * sizeof(int *));
    for(int i=0; i<rB; i++) {
        B[i] = (int*)malloc(cB * sizeof(int));
    }
    result = (int**)malloc(rA * sizeof(int *));
    for(int i=0; i<rA; i++) {
        result[i] = (int*)malloc(cB * sizeof(int));
    }
    printf("Enter elements of Matrix A:\n");
    for(int i = 0; i < rA; i++)
        for(int j = 0; j < cA; j++)
            scanf("%d", &A[i][j]);
    printf("Enter elements of Matrix B:\n");
    for(int i = 0; i < rB; i++)
        for(int j = 0; j < cB; j++)
            scanf("%d", &B[i][j]);
    pthread_t threads[rA];
    for(int i=0; i<rA; i++) {
        int *thread_arg = (int *)malloc(sizeof(int));
        *thread_arg = i;
        pthread_create(&threads[i], NULL, &MatrixMulti, (void *)thread_arg);
    }
    for(int i=0; i<rA; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Result of Matrix A * Matrix B:\n");
    for(int i=0; i<rA; i++) {
        for(int j=0; j<cB; j++) {
            if(j != 0) printf(" ");
            printf("%d", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}