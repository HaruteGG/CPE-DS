#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int m, n, p;
    int shmid;
    int *shared_memory;
    printf("Please enter the size of matrices A:m*n , B:n*p\n");
    scanf("%d %d %d", &m, &n, &p);
    long total_elements = 3 + (m * n) + (n * p) + (m * p);
    shmid = shmget(IPC_PRIVATE, total_elements * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }
    shared_memory = (int *)shmat(shmid, NULL, 0);
    if (shared_memory == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }
    printf("Memory attached at %p\n", (void*)shared_memory);
    int *dimensions = shared_memory;
    dimensions[0] = m;
    dimensions[1] = n;
    dimensions[2] = p;
    
    int *matrix_A = dimensions + 3;
    int *matrix_B = matrix_A + (m * n);
    int *matrix_C = matrix_B + (n * p);
    printf("Enter elements of matrix A:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &matrix_A[i * n + j]);
        }
    }
    printf("Enter elements of matrix B:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            scanf("%d", &matrix_B[i * p + j]);
        }
    }
    pid_t pid;
    for(int i = 0; i < m; i++) {
        pid = fork();
        if(pid < 0) {
            perror("fork failed");
            exit(1);
        }
        else if (pid == 0) {
            for(int j = 0; j < p; j++) {
                int sum = 0;
                for(int k = 0; k < n; k++) {
                    sum += matrix_A[i * n + k] * matrix_B[k * p + j];
                }
                matrix_C[i * p + j] = sum;
            }
            exit(0);
        }
    }
    for(int i = 0; i < m; i++) {
        wait(NULL);
    }
    printf("Result of Matrix A * Matrix B:\n");
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < p; j++) {
            printf("%d ", matrix_C[i * p + j]);
        }
        printf("\n");
    }
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
