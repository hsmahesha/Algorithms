/*
 *
 * Backtracking based algorithm which finds all possible solutions to n-queens
 * problem.
 *
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define N  8    // Number of queens

vector<int> soln = vector<int>(N);  // Solution vector

/*
 * Initializes the solution vector to hold the value -1 before backtracking
 * process starts. Because, we start indexing our `soln` vector from 0, and
 * is initialized with 0s when it is constructed.
 */
void initSolnVector() {
    for (int i = 0; i < N; i++) {
        soln[i] = -1;
    }
}

/*
 * Prints the current solution to stdout
 */
void printSoln() {
    for (int i=0; i < N; i++) {
        cout << soln[i] << " ";
    }
    cout << endl;
}

/*
 * Checks if the queen `r' can be placed in an index (r, j)
 */
bool isLegal(int j, int r) {
    for (int i = 0; i < r; i++) {
        // The column `j` is already selected? (or) diagonal entries?
        if (soln[i] == j || abs(soln[i] - j) == abs(r - i))
            return false;
    }
    return true;
}

/*
 * Finds all possible solutions through systematic recursive exploration of
 * solution space
 */
void nQueens(int r) {
    // All the N queens are successfully placed on the board?
    if (r == N) {
        printSoln();
    } else {
        // Search for an index (r, j) where the current queen `r` can be placed
        for (int j = 0; j < N ; j++) {
            if (isLegal(j, r)) {
                soln[r] = j;
                nQueens(r+1);
            }
        }
    }
}

int main(int args, char* argv[]) {
    initSolnVector();   // Initilize the solution vector to -1
    nQueens(0);   // Initiate backtracking by passing first queen
}
