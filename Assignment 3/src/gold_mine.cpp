// Gold mine: most gold collected moving right, right-up or right-down, starting in any row of column 0
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int goldMine(const vector<vector<int>>& mine, vector<int>& pathRows) {
    int m = mine.size(), n = mine[0].size();
    vector<vector<int>> gold(m, vector<int>(n, 0));   // gold[i][j]: most gold starting from (i, j)
    for (int i = 0; i < m; i++) gold[i][n - 1] = mine[i][n - 1];   // last column: no move left
    for (int j = n - 2; j >= 0; j--) {
        for (int i = 0; i < m; i++) {
            int best = gold[i][j + 1];                                  // right
            if (i > 0) best = max(best, gold[i - 1][j + 1]);            // right-up
            if (i < m - 1) best = max(best, gold[i + 1][j + 1]);        // right-down
            gold[i][j] = mine[i][j] + best;
        }
    }
    int row = 0;                                       // best starting row in the first column
    for (int i = 1; i < m; i++) if (gold[i][0] > gold[row][0]) row = i;
    int answer = gold[row][0];
    pathRows.clear();                                  // follow the best moves to recover the path
    for (int j = 0; j < n; j++) {
        pathRows.push_back(row);
        if (j == n - 1) break;
        int next = row;
        if (row > 0 && gold[row - 1][j + 1] > gold[next][j + 1]) next = row - 1;
        if (row < m - 1 && gold[row + 1][j + 1] > gold[next][j + 1]) next = row + 1;
        row = next;
    }
    return answer;
}

void solve(const vector<vector<int>>& mine) {
    vector<int> rows;
    int answer = goldMine(mine, rows);
    cout << "most gold: " << answer << endl << "path:";
    for (int j = 0; j < (int)rows.size(); j++)
        cout << " " << mine[rows[j]][j] << " (" << rows[j] << "," << j << ")";
    cout << endl;
}

int main() {
    vector<vector<int>> mine1 = {{1, 3, 3},
                                 {2, 1, 4},
                                 {0, 6, 4}};
    vector<vector<int>> mine2 = {{1, 3, 1, 5},
                                 {2, 2, 4, 1},
                                 {5, 0, 2, 3},
                                 {0, 6, 1, 2}};
    solve(mine1);
    solve(mine2);
    return 0;
}
