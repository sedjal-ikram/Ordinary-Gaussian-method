#include <iostream>
using namespace std;

// Read the matrix and the vector

void readsystem(double A[10][10], double B[10], int &n) {
    cout << "Enter the number of equations "; // Ask the user for the number of equations
    cin >> n; // Read the number entered by the user

    cout << "\nEnter the coefficient of the matrix\n"; // Ask for the coefficients of matrix A
    for (int i = 0; i < n; i++) { // Loop through each row
        for (int j = 0; j < n; j++) { // Loop through each column
            cin >> A[i][j]; // Read each element of the matrix A
        }
    }

    cout << "\nEnter the elements of vector B :\n";
    for (int i = 0; i < n; i++) { // Ask for the elements of vector B
        cin >> B[i]; // Read each element of vector B
    }
}

// Forward elimination

void forwardElimination(double A[10][10], double B[10], int n) { 
    for (int k = 0; k < n - 1; k++) { // Loop through each pivot row (except the last one)

        // ? Check if the pivot element is zero
        if (A[k][k] == 0) {
            int swapRow = -1; // Variable to store the index of a row to swap with

            // Search for a row below that has a non-zero element in the same column
            for (int i = k + 1; i < n; i++) {
                if (A[i][k] != 0) { // If a non-zero pivot is found
                    swapRow = i;    // Remember this row index
                    break;          // Stop searching (we found a valid row)
                }
            }

            // If no non-zero pivot is found, the system cannot be solved
            if (swapRow == -1) {
                cout << "Error: zero pivot and no row to swap. The system cannot be solved.\n";
                return; // Exit the function early because elimination cannot continue
            }

            // Swap the two rows in matrix A 
            for (int j = 0; j < n; j++) {
                swap(A[k][j], A[swapRow][j]); // Exchange each element of the two rows
            }

            // Swap the corresponding elements in vector B to keep the system consistent
            swap(B[k], B[swapRow]);
        }

        for (int i = k + 1; i < n; i++) { // For each row below the pivot
            double factor = A[i][k] / A[k][k]; // Compute the elimination factor
            for (int j = k; j < n; j++) { // Apply the elimination to all columns
                A[i][j] -= factor * A[k][j]; // Subtract (factor * pivot row) from the current row
            }
            B[i] -= factor * B[k]; // Update the corresponding value in vector B
        }
    }
}

// Back substitution

void backSubstitution(double A[10][10], double B[10], double X[10], int n) {
    for (int i = n - 1; i >= 0; i--) { // Start from the last equation and go upward
        double somme = 0;     // Variable to store the sum of known terms
        for (int j = i + 1; j < n; j++) { // Compute the sum of A[i][j] * X[j] for known X[j]
            somme += A[i][j] * X[j];
        }
        X[i] = (B[i] - somme) / A[i][i];  // Compute the value of the unknown X[i]
    }
}

// Gauss method

void gauss(double A[10][10], double B[10], double X[10], int n) {
    forwardElimination(A, B, n); // Step 1: Transform the system into an upper triangular form
    backSubstitution(A, B, X, n); // Step 2: Compute the solution by back substitution
}

// Affichage

void display(double X[10], int n) {
    cout << "\nthe solution of the system is :\n";
    for (int i = 0; i < n; i++) { // Loop through each solution variable
        cout << "x" << i + 1 << " = " << X[i] << endl; // Display xi = value
    }
}

int main() {
    int n;
    double A[10][10], B[10], X[10];
    
    readsystem(A, B, n);      // reading the data 
    gauss(A, B, X, n);         // computing the solution
    display(X, n);    // Displaying the result

    return 0;
}
