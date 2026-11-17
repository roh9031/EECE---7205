// Longest palindromic subsequence: L[i][j] = longest palindrome inside s[i..j]
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int lps(const string& s, string& palindrome) {
    int n = s.size();
    vector<vector<int>> L(n, vector<int>(n, 0));      // cells with i > j stay 0 (empty substring)
    for (int i = 0; i < n; i++) L[i][i] = 1;          // one character is a palindrome
    for (int len = 2; len <= n; len++) {              // by increasing substring length
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) L[i][j] = L[i + 1][j - 1] + 2;          // use both ends
            else L[i][j] = max(L[i + 1][j], L[i][j - 1]);              // drop one end
        }
    }
    string left, middle;                              // walk back through the table
    int i = 0, j = n - 1;
    while (i <= j) {
        if (i == j) { middle = s[i]; break; }
        if (s[i] == s[j]) { left += s[i]; i++; j--; }
        else if (L[i + 1][j] >= L[i][j - 1]) i++;
        else j--;
    }
    string right = left;
    reverse(right.begin(), right.end());
    palindrome = left + middle + right;
    return L[0][n - 1];
}

int main() {
    vector<string> tests = {"BBABCBCAB", "AGBDBA"};
    for (const string& s : tests) {
        string p;
        int len = lps(s, p);
        cout << s << ": length " << len << ", for example " << p << endl;
    }
    return 0;
}
