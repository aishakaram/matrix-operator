#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef vector<vector<double>> Matrix;

// Function to get matrix input from the user
Matrix getMatrix(int rows, int cols, string name) {
    Matrix mat(rows, vector<double>(cols));
    cout << "Enter elements for " << name << " (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> mat[i][j];
        }
    }
    return mat;
}

// Function to display a matrix
void displayMatrix(const Matrix &mat) {
    for (const auto &row : mat) {
        for (double val : row) {
            cout << setw(8) << val << " ";
        }
        cout << endl;
    }
}

// Function to add two matrices
Matrix addMatrices(const Matrix &A, const Matrix &B) {
    int rows = A.size(), cols = A[0].size();
    Matrix result(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}

// Function to subtract two matrices
Matrix subtractMatrices(const Matrix &A, const Matrix &B) {
    int rows = A.size(), cols = A[0].size();
    Matrix result(rows, vector<double>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}

// Function to multiply two matrices
Matrix multiplyMatrices(const Matrix &A, const Matrix &B) {
    int rowsA = A.size(), colsA = A[0].size(), colsB = B[0].size();
    Matrix result(rowsA, vector<double>(colsB, 0));
    
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsB; j++)
            for (int k = 0; k < colsA; k++)
                result[i][j] += A[i][k] * B[k][j];

    return result;
}

// Function to find the transpose of a matrix
Matrix transposeMatrix(const Matrix &A) {
    int rows = A.size(), cols = A[0].size();
    Matrix result(cols, vector<double>(rows));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[j][i] = A[i][j];
    return result;
}

// Function to calculate the inverse of a square matrix using Gaussian elimination
Matrix inverseMatrix(Matrix A) {
    int n = A.size();
    Matrix inverse(n, vector<double>(n, 0));

    // Initialize the identity matrix
    for (int i = 0; i < n; i++)
        inverse[i][i] = 1;

    // Perform Gaussian elimination
    for (int i = 0; i < n; i++) {
        if (A[i][i] == 0) {
            cout << "Error: Singular matrix, inverse does not exist.\n";
            return {};
        }
        
        double diag = A[i][i];
        for (int j = 0; j < n; j++) {
            A[i][j] /= diag;
            inverse[i][j] /= diag;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = A[k][i];
                for (int j = 0; j < n; j++) {
                    A[k][j] -= factor * A[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }
    return inverse;
}

int main() {
    int rows, cols;
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    Matrix A = getMatrix(rows, cols, "Matrix A");

    while (true) {
        cout << "\nChoose an operation:\n";
        cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Transpose\n5. Inverse\n6. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1 || choice == 2) {
            Matrix B = getMatrix(rows, cols, "Matrix B");
            Matrix result = (choice == 1) ? addMatrices(A, B) : subtractMatrices(A, B);
            cout << "\nResult:\n";
            displayMatrix(result);
        }
        else if (choice == 3) {
            int r2, c2;
            cout << "Enter number of rows for Matrix B: ";
            cin >> r2;
            cout << "Enter number of columns for Matrix B: ";
            cin >> c2;
            if (cols != r2) {
                cout << "Error: Columns of A must match rows of B for multiplication.\n";
                continue;
            }
            Matrix B = getMatrix(r2, c2, "Matrix B");
            Matrix result = multiplyMatrices(A, B);
            cout << "\nResult:\n";
            displayMatrix(result);
        }
        else if (choice == 4) {
            Matrix result = transposeMatrix(A);
            cout << "\nTranspose:\n";
            displayMatrix(result);
        }
        else if (choice == 5) {
            if (rows != cols) {
                cout << "Error: Inverse can only be calculated for square matrices.\n";
                continue;
            }
            Matrix result = inverseMatrix(A);
            if (!result.empty()) {
                cout << "\nInverse:\n";
                displayMatrix(result);
            }
        }
        else if (choice == 6) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    }

    return 0;
}