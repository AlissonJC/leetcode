/*
 * LeetCode 808 - Soup Servings
 *
 * Two soups A and B each start with n mL. Every turn one of four serving
 * operations is chosen uniformly at random (probability 0.25 each), pouring
 * from A and B simultaneously: (100,0), (75,25), (50,50), (25,75) mL. If an
 * operation asks for more than a soup has left, it pours only what remains. The
 * process stops the instant either soup is emptied. Return the probability that
 * A empties strictly before B, plus half the probability that both empty on the
 * same turn. An answer within 1e-5 of the true value is accepted.
 *
 * Input  : int n (0 <= n <= 1e9). Output : double — the probability described.
 *
 * Approach: every poured amount is a multiple of 25 mL, so rescale by 25 and
 *   work in "chunks": m = ceil(n / 25). The four operations become, in chunks,
 *   (4,0), (3,1), (2,2), (1,3) — note each pours exactly 4 chunks total, so the
 *   combined remaining a+b drops by 4 every turn (recursion stays shallow).
 *   Let dp(a,b) be the requested probability when a chunks of A and b of B
 *   remain. Base cases capture who runs out: both out together -> 0.5, only A
 *   out -> 1.0, only B out -> 0.0 (check "both" first so a tie is not miscounted
 *   as an A-first win). The recurrence averages the four next states with weight
 *   0.25 and is memoized. Because each operation pours on average more from A
 *   (62.5 mL) than from B (37.5 mL), the probability tends to 1 as n grows; past
 *   n = 4800 it is already within 1e-5 of 1, so return 1.0 directly and keep the
 *   DP table bounded (m <= 192).
 *
 * Complexity: O(m^2) time and space with m = min(ceil(n/25), 192), i.e. O(1)
 *   after the large-n cutoff; the dominant cost is filling the memo table.
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    double soupServings(int n) {
        // For large n the answer is indistinguishable from 1 within tolerance.
        if (n >= 4800) return 1.0;

        // Rescale to 25-mL chunks, rounding up: a partial chunk still empties in
        // one "pour all that remains" step, so ceil is the correct reduction.
        int m = (n + 24) / 25;

        // memo[a][b] < 0 means "not computed yet"; valid probabilities are >= 0.
        vector<vector<double>> memo(m + 1, vector<double>(m + 1, -1.0));
        return dp(m, m, memo);
    }

private:
    double dp(int a, int b, vector<vector<double>>& memo) {
        // Order matters: test the simultaneous-empty case before the A-empty
        // case, otherwise a tie would be scored as a full A-first win.
        if (a <= 0 && b <= 0) return 0.5;  // both used up on the same turn
        if (a <= 0) return 1.0;            // A used up first
        if (b <= 0) return 0.0;            // B used up first

        if (memo[a][b] >= 0.0) return memo[a][b];

        // Average the four equally likely operations; clamp to 0 so we never
        // index with a negative remaining amount.
        double r = 0.25 * (dp(max(0, a - 4), b,             memo)
                         + dp(max(0, a - 3), max(0, b - 1), memo)
                         + dp(max(0, a - 2), max(0, b - 2), memo)
                         + dp(max(0, a - 1), max(0, b - 3), memo));
        return memo[a][b] = r;
    }
};
