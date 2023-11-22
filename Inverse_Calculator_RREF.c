#include <stdio.h>
#define MAX_SIZE 10

void printAugmentedMatrix(int size, double matrixA[MAX_SIZE][MAX_SIZE], double matrixB[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.2f\t", matrixA[i][j]);
        }
        printf("| ");
        for (int j = 0; j < size; j++) {
            printf("%.2f\t", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void swapRows(int size, double matrixA[MAX_SIZE][MAX_SIZE], double matrixB[MAX_SIZE][MAX_SIZE], int row1, int row2) {
    for (int j = 0; j < size; j++) {
        double tempA = matrixA[row1][j];
        matrixA[row1][j] = matrixA[row2][j];
        matrixA[row2][j] = tempA;

        double tempB = matrixB[row1][j];
        matrixB[row1][j] = matrixB[row2][j];
        matrixB[row2][j] = tempB;
    }
}

void scaleRow(int size, double matrixA[MAX_SIZE][MAX_SIZE],
 double matrixB[MAX_SIZE][MAX_SIZE], int row, double scalar) {
    for (int j = 0; j < size; j++) {
        matrixA[row][j] *= scalar;
        matrixB[row][j] *= scalar;
    }
}

void addRows(int size, double matrixA[MAX_SIZE][MAX_SIZE], double matrixB[MAX_SIZE][MAX_SIZE], int destRow, int sourceRow, double scalar) {
    for (int j = 0; j < size; j++) {
        matrixA[destRow][j] += scalar * matrixA[sourceRow][j];
        matrixB[destRow][j] += scalar * matrixB[sourceRow][j];
    }
}

void inverse(int size, double matrixA[MAX_SIZE][MAX_SIZE], double matrixB[MAX_SIZE][MAX_SIZE]) {
    int lead = 0;

    for (int i = 0; i < size; i++) {
        if (lead >= size)
            break;

        int i0 = i;
        while (matrixA[i0][lead] == 0.0) {
            i0++;

            if (i0 == size) {
                i0 = i;
                lead++;

                if (size == lead)
                    break;
            }
        }

        scaleRow(size, matrixA, matrixB, i0, 1.0 / matrixA[i0][lead]);

        for (int i1 = 0; i1 < size; i1++) {
            if (i1 != i0) {
                double factor = -matrixA[i1][lead];
                addRows(size, matrixA, matrixB, i1, i0, factor);
            }
        }

        lead++;
        printf("Step %d:\n", lead);
        printAugmentedMatrix(size, matrixA, matrixB);
    }
}

int main() {
    int size;

    printf("Welcome to Inverse Calculator\n");
        printf("\n");

    printf(" Square Matrix Size: ");
    scanf("%d", &size);

    if (size > MAX_SIZE) {
        printf("Invalid matrix size. Exiting...\n");
        return 1;
    }

    double matrixA[MAX_SIZE][MAX_SIZE];
    double matrixB[MAX_SIZE][MAX_SIZE];

    printf("Enter the matrix A elements:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%lf", &matrixA[i][j]);
            // Initialize matrixB as the identity matrix
            matrixB[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    printf("Step 0:\n");
    printAugmentedMatrix(size, matrixA, matrixB);

    // Perform row reduction on both matrices A and B simultaneously
    inverse(size, matrixA, matrixB);

    printf("Inverse Matrix of A is:\n");
    printAugmentedMatrix(size, matrixA, matrixB);

    printf("Thank You for Using Inverse Calculator!!!\n");

    return 0;
}

