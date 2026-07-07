/*
 * LeetCode 79 - Word Search
 *
 * Given an m x n grid of letters `board` and a string `word`, return true if `word`
 * can be spelled by a path of sequentially adjacent cells (horizontal/vertical
 * neighbors), where no single cell is used more than once.
 *
 * Input  : vector<vector<char>>& board, string word. Output : bool — is word present.
 *
 * Constraints: 1 <= m, n <= 6; 1 <= word.length <= 15; board and word are English
 *   letters (upper/lowercase).
 *
 * Approach: Depth-first search with backtracking, launched from every cell as a
 *   possible first letter. dfs(i, j, k) tries to match word[k] at board[i][j]: it fails
 *   immediately on an out-of-bounds cell or a letter mismatch, and succeeds once k
 *   reaches the last index (the current cell already matched the final letter). To
 *   forbid reusing a cell within the current path, mark it in place by overwriting it
 *   with '#', a sentinel that can never equal a letter of `word`, then explore the four
 *   neighbors for word[k+1]; restore the original letter on the way out so the board is
 *   left unchanged and other start positions see a clean grid. This in-place marking
 *   avoids a separate visited matrix (O(1) extra space). With m, n <= 6 the search is
 *   tiny; the mismatch check prunes dead branches instantly (the requested pruning).
 *
 * Complexity: O(m * n * 4^L) worst case, L = word.length (each of m*n starts branches
 *   into up to 4 directions for L steps); O(L) recursion depth, O(1) extra space.
 */

#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = (int)board.size(), n = (int)board[0].size();
        // Try every cell as the starting letter of the word.
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (dfs(board, word, 0, i, j, m, n)) return true;
        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, const string& word,
             int k, int i, int j, int m, int n) {
        // Off the board or the letter here does not match word[k] -> this path dies.
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[k]) return false;
        // Matched the final letter: the whole word has been found.
        if (k == (int)word.size() - 1) return true;

        char saved = board[i][j];
        board[i][j] = '#';   // mark visited: '#' is not a letter, so it blocks reuse

        // Extend the path to the four orthogonal neighbors for the next letter.
        bool found = dfs(board, word, k + 1, i + 1, j, m, n) ||
                     dfs(board, word, k + 1, i - 1, j, m, n) ||
                     dfs(board, word, k + 1, i, j + 1, m, n) ||
                     dfs(board, word, k + 1, i, j - 1, m, n);

        board[i][j] = saved; // restore so the grid is unchanged for other starts
        return found;
    }
};
