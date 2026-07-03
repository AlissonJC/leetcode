/*
 * LeetCode 60 - Permutation Sequence
 *
 * The set {1, 2, ..., n} has n! distinct permutations. Listing them in ascending
 * (lexicographic) order and numbering them from 1, return the k-th permutation
 * as a string of digits.
 *
 * Input  : int n (size of the set), int k (1-indexed rank of the permutation).
 * Output : string - the k-th permutation of "12...n".
 *
 * Constraints: 1 <= n <= 9; 1 <= k <= n!.
 *
 * Approach: construct the answer digit by digit with the factorial number
 *   system instead of generating permutations one at a time. Among the ordered
 *   permutations, those sharing a fixed leading digit form a contiguous block of
 *   (n-1)! entries. So the leading digit is the (k-1)/(n-1)!-th smallest digit
 *   not yet used; after choosing it, drop into that block by replacing k-1 with
 *   (k-1) mod (n-1)! and repeat for the next position using (n-2)!, then
 *   (n-3)!, and so on. Keeping the still-unused digits in ascending order makes
 *   each index directly select the correct (lexicographically i-th smallest)
 *   digit. Working 0-indexed (k-1) throughout avoids off-by-one errors.
 *
 * Complexity: O(n^2) time - n positions, each removing a digit from the
 *   candidate list in O(n); O(n) space. With n <= 9, 9! = 362880 and every
 *   factorial fit comfortably in a 32-bit int.
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        // Factorials 0!..n!; fact[m] = number of orderings of m free digits.
        vector<int> fact(n + 1, 1);
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;

        // Candidate digits 1..n kept in ascending order so index i is the
        // lexicographically i-th smallest remaining digit.
        vector<int> digits;
        for (int d = 1; d <= n; ++d) digits.push_back(d);

        --k;                 // switch to 0-indexed rank
        string result;
        for (int i = 0; i < n; ++i) {
            int blockSize = fact[n - 1 - i];   // (n-1-i)! permutations per leading digit
            int idx = k / blockSize;           // which remaining digit leads this slot
            result.push_back((char)('0' + digits[idx]));
            digits.erase(digits.begin() + idx);   // that digit is now used
            k %= blockSize;                    // descend into the chosen block
        }
        return result;
    }
};
