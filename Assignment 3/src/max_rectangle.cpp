// Maximum sum rectangle: fix columns l..r, add up each row, run Kadane on the row sums
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Best { int sum, top, bottom; };

Best kadane(const vector<int>& a) {               // best block of consecutive entries of a
    int cur = a[0], start = 0;
    Best b = {a[0], 0, 0};
    for (int i = 1; i < (int)a.size(); i++) {
        if (cur < 0) { cur = a[i]; start = i; }   // a negative prefix only hurts: restart
        else cur += a[i];                         // extend the current block
        if (cur > b.sum) b = {cur, start, i};
    }
    return b;
}

int main() {
    vector<vector<int>> A = {{ 1,  2, -1, -4, -20},
                             {-8, -3,  4,  2,   1},
                             { 3,  8, 10,  1,   3},
                             {-4, -1,  1,  7,  -6}};
    int m = A.size(), n = A[0].size();
    int bestSum = INT_MIN, top = 0, left = 0, bottom = 0, right = 0;
    for (int l = 0; l < n; l++) {
        vector<int> rowSum(m, 0);                 // sum of row i over columns l..r
        for (int r = l; r < n; r++) {
            for (int i = 0; i < m; i++) rowSum[i] += A[i][r];   // add one more column
            Best b = kadane(rowSum);
            if (b.sum > bestSum) {
                bestSum = b.sum; top = b.top; bottom = b.bottom; left = l; right = r;
            }
        }
    }
    cout << "max sum: " << bestSum << endl;
    cout << "top-left: (" << top << "," << left << "), bottom-right: (" << bottom << "," << right << ")" << endl;
    return 0;
}
