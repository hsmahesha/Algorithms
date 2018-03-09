/*
 *
 * Backtracking based algorithm which finds all possible permutation of a given
 * set (distinct) integers of size `N`.
 *
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define N  4    // Size of a given set

vector<int> iset = vector<int>(N);  // Given set of elements whose permutations
                                    // need to be computed


/*
 * Prints the current permutation to stdout
 */
void printSoln() {
    cout << "{ ";
    for (int i = 0; i < N; i++) {
        cout << iset[i] << " ";
    }
    cout << "}" << endl;
}

/*
 *  Swaps the elements at the index i, j of array `iset'
 */
void swap(int i, int j) {
    int t = iset[i];
    iset[i] = iset[j];
    iset[j] = t;
}

/*
 * Finds all possible permutations of a given set through systematic recursive
 * exploration of solution space
 */
void genPerm(int k) {
    if (k == N-1) {
        printSoln();
    } else {
        for (int i = k; i < N; i++) {
            swap(i, k);
            genPerm(k+1);
            swap(i, k);
        }
    }
}

/*
 * Constructs an input set of first `N` positive integers
 */
void constructSet() {
    for (int i = 0; i < N; i++) {
        iset[i] = i+1;
    }
}

int main(int args, char* argv[]) {
    // Store first `N' integers in an array, and treat it as a set.
    constructSet();

    // Initiate backtracking
    genPerm(0);
}
