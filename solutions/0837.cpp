/*
 * LeetCode 837 - New 21 Game
 *
 * Alice starts at 0 points and keeps drawing while her score is strictly less
 * than k. Each draw adds a uniformly random integer from [1, maxPts], draws are
 * independent, and she stops the moment her score reaches k or more. Return the
 * probability that her final score is at most n. An answer within 1e-5 of the
 * true value is accepted.
 *
 * Input  : ints n, k, maxPts. Output : double — P(final score <= n).
 *
 * Constraints: 0 <= k <= n <= 1e4; 1 <= maxPts <= 1e4. The answer is a
 *   probability in [0, 1]; doubles carry ample precision for the 1e-5 tolerance.
 *
 * Approach: let dp[i] be the probability that Alice's score is exactly i. A
 *   score i is reached only by drawing from a still-active score j (j < k) with
 *   i - j in [1, maxPts], so dp[i] = (sum of dp[j] over active j in
 *   [i-maxPts, i-1]) / maxPts. Each draw outcome has weight 1/maxPts, hence the
 *   division. Maintain that sum as a sliding window instead of recomputing it:
 *   when moving from i to i+1, add dp[i] if i is still active (i < k) and drop
 *   dp[i-maxPts] as it leaves the window. Scores in [k, n] are terminal (she has
 *   stopped), so accumulate them into the answer. Two shortcuts return 1.0
 *   immediately: k == 0 (she never draws, final score 0 <= n) and
 *   n >= k-1+maxPts (the largest reachable score k-1+maxPts is already <= n).
 *
 * Complexity: O(n) time — one pass with O(1) window updates; O(n) space for dp.
 */

#include <vector>
using namespace std;

class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        // k == 0: Alice is already "not less than k", so she never draws and her
        // score stays 0, which is <= n. Handle first to avoid a k-1 of -1 below.
        if (k == 0 || n >= k - 1 + maxPts) return 1.0;

        vector<double> dp(n + 1, 0.0);
        dp[0] = 1.0;                 // she always starts at score 0

        // windowSum holds the probability mass of active scores that can reach
        // the score currently being computed. Before i = 1 the only such score
        // is 0, so the window starts at dp[0].
        double windowSum = 1.0;
        double answer = 0.0;

        for (int i = 1; i <= n; ++i) {
            // Probability of landing exactly on i: average of the active window.
            dp[i] = windowSum / maxPts;

            if (i < k)
                windowSum += dp[i];   // i is still active; it can spawn later scores
            else
                answer += dp[i];      // i >= k is a terminal score we want to count

            // The score i-maxPts can no longer reach i+1, so it leaves the window
            // (only if it was an active score in the first place).
            int leaving = i - maxPts;
            if (leaving >= 0 && leaving < k)
                windowSum -= dp[leaving];
        }

        return answer;
    }
};
