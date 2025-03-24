#include <bits/stdc++.h>
using namespace std;

// Function to add two matrices
vector<vector<int>> addMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

// Strassen's Matrix Multiplication
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Base case: If matrix is 1x1, multiply directly
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // Splitting matrices into submatrices
    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute the seven Strassen's intermediate matrices
    vector<vector<int>> M1 = strassen(addMatrix(A11, A22), addMatrix(B11, B22));
    vector<vector<int>> M2 = strassen(addMatrix(A21, A22), B11);
    vector<vector<int>> M3 = strassen(A11, subtractMatrix(B12, B22));
    vector<vector<int>> M4 = strassen(A22, subtractMatrix(B21, B11));
    vector<vector<int>> M5 = strassen(addMatrix(A11, A12), B22);
    vector<vector<int>> M6 = strassen(subtractMatrix(A21, A11), addMatrix(B11, B12));
    vector<vector<int>> M7 = strassen(subtractMatrix(A12, A22), addMatrix(B21, B22));

    // Construct result matrix C using Strassen's formulas
    vector<vector<int>> C11 = addMatrix(subtractMatrix(addMatrix(M1, M4), M5), M7);
    vector<vector<int>> C12 = addMatrix(M3, M5);
    vector<vector<int>> C21 = addMatrix(M2, M4);
    vector<vector<int>> C22 = addMatrix(subtractMatrix(addMatrix(M1, M3), M2), M6);

    // Combining results into final matrix
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}

// Function to print matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    vector<vector<int>> A = {{1, 2, 3, 4},
                              {5, 6, 7, 8},
                              {9, 10, 11, 12},
                              {13, 14, 15, 16}};

    vector<vector<int>> B = {{1, 2, 3, 4},
                              {5, 6, 7, 8},
                              {9, 10, 11, 12},
                              {13, 14, 15, 16}};

    vector<vector<int>> C = strassen(A, B);

    cout << "Resultant Matrix:\n";
    printMatrix(C);

    return 0;
}
