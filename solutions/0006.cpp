/*
 * LeetCode 6 - Zigzag Conversion
 *
 * Write the characters of s in a zigzag across numRows rows: go straight down
 * row by row, then move diagonally up to the top, and repeat. After the whole
 * string is placed, read the grid row by row (top to bottom) and concatenate to
 * get the answer. Example with numRows = 3:
 *     P   A   H   N
 *     A P L S I I G
 *     Y   I   R
 *   read row by row -> "PAHNAPLSIIGYIR".
 *
 * Input  : string s, int numRows (function arguments, no stdin/stdout).
 * Output : the zigzag-converted string.
 *
 * Constraints: 1 <= s.length <= 1000; s has English letters, ',' and '.';
 *              1 <= numRows <= 1000.
 *
 * Approach: there is no need to build the 2D grid. Walk through s once while
 *   tracking the current row and a vertical direction. Append each character to
 *   that row's buffer, and flip the direction whenever the top row (0) or the
 *   bottom row (numRows-1) is reached — that bounce is exactly what produces the
 *   zigzag. Concatenating the row buffers in order yields the line-by-line read.
 *
 * Edge case: numRows == 1 has no bottom row to bounce off, so the direction
 *   logic does not apply; the zigzag degenerates to the original string.
 *
 * Complexity: O(n) time (one pass plus one concatenation) and O(n) space for the
 *   row buffers, where n = s.length.
 */

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;        // single row: nothing zigzags

        // Only min(n, numRows) rows are ever touched; extra rows would stay
        // empty when numRows > n, so cap the count to avoid useless buffers.
        vector<string> rows(min((int)s.size(), numRows));

        int curRow = 0;
        bool goingDown = false;            // flips to true on the first character (at row 0)

        for (char c : s) {
            rows[curRow] += c;
            // At the top or bottom row the path reverses vertical direction.
            if (curRow == 0 || curRow == numRows - 1)
                goingDown = !goingDown;
            curRow += goingDown ? 1 : -1;
        }

        // Read the zigzag line by line: rows concatenated top to bottom.
        string result;
        result.reserve(s.size());
        for (const string& row : rows)
            result += row;
        return result;
    }
};
