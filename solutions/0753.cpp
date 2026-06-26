/*
 * LeetCode 753 - Cracking the Safe
 *
 * A password is a sequence of n digits, each in [0, k-1]. As digits are typed, the
 * safe always checks the most recent n typed digits, so a single entered string
 * unlocks the safe if every possible n-digit password appears somewhere as a
 * length-n substring. Return any shortest such string.
 *
 * Input  : int n, int k. Output : string — a minimum-length unlocking sequence.
 *
 * Constraints: 1 <= n <= 4; 1 <= k <= 10; 1 <= k^n <= 4096. There are exactly k^n
 *   distinct passwords, so the alphabet and lengths are tiny.
 *
 * Approach: build a de Bruijn sequence B(k, n), the shortest string containing
 *   every length-n word over a k-symbol alphabet exactly once. Model it as a graph
 *   whose nodes are the (n-1)-length prefixes and whose edges are the n-length
 *   passwords: appending digit d to prefix p forms the password p+d and moves to
 *   the prefix (p+d) without its first character. An Eulerian circuit using every
 *   edge once spells a de Bruijn sequence, found with Hierholzer's algorithm:
 *   from the current node, walk down each not-yet-used outgoing edge, and append
 *   that edge's digit only after its subtree is fully explored (post-order). Start
 *   from the all-zeros prefix; the produced digits plus that starting prefix form
 *   the answer, of length k^n + (n - 1), which is optimal.
 *
 * Complexity: O(k^n * n) time (one visit per edge, each doing O(n) string work)
 *   and O(k^n * n) space for the visited-password set and the recursion.
 */

#include <string>
#include <unordered_set>
using namespace std;

class Solution {
    unordered_set<string> seen;     // passwords (edges) already walked
    string ans;                     // digits emitted in post-order
    int K;

    void dfs(const string& node) {
        for (int x = 0; x < K; ++x) {
            string edge = node + char('0' + x);     // the n-digit password p + x
            // Walk each password edge exactly once (insert returns false if present).
            if (seen.insert(edge).second) {
                dfs(edge.substr(1));                 // move to the next (n-1)-prefix
                ans += char('0' + x);                // emit after the subtree is done
            }
        }
    }

public:
    string crackSafe(int n, int k) {
        seen.clear();
        ans.clear();
        K = k;

        // The starting node is the (n-1)-length all-zeros prefix (empty when n == 1).
        string start(n - 1, '0');
        dfs(start);

        // The Euler walk emitted one digit per password; prepend-equivalent the
        // start prefix so the very first n-window is also a valid password.
        return ans + start;
    }
};
