/*
 *
 * Backtracking based algorithm which finds all possible subsets of a given set
 * of size `N`.
 *
 * Note: This implementation simply prints subsets of the set of first `N`
 *       positive integers. By tweaking this implemention a bit, we can make it
 *       to work for any given set, though I have not taken care of it.
 *
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define N  4    // Size of a given set

vector<int> soln = vector<int>(N);  // Solution vector

/*
 * Prints the current subset to stdout
 */
void printSoln() {
    cout << "{ ";
    for (int i = 0; i < N; i++) {
        if (soln[i] == 1)
           cout << i+1 << " ";
    }
    cout << "}" << endl;
}

/*
 * Finds all possible subsets of a given set through systematic recursive
 * exploration of solution space
 */
void Subset(int i) {
    if (i == N) {
        printSoln();
    } else {
        for (int j = 0; j <= 1; j++) {
           soln[i] = j;
           Subset(i+1);
        }
    }
}

int main(int args, char* argv[]) {
    // Initiate backtracking
    Subset(0);
}
