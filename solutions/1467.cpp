/*
 * LeetCode 1467 - Probability of Two Boxes Having The Same Number of Distinct Balls
 *
 * There are 2n balls of k distinct colors; balls[i] is how many balls have color
 * i. The balls are shuffled uniformly at random, the first n go into box 1 and
 * the last n into box 2 (the two boxes are ordered/distinguishable). Return the
 * probability that both boxes end up with the same number of *distinct* colors.
 *
 * Input  : vector<int> balls of size k. Output : double — the probability.
 *
 * Constraints: 1 <= k <= 8; 1 <= balls[i] <= 6; sum(balls) is even (= 2n, so
 *   n <= 24). Small enough to enumerate every way to split the colors.
 *
 * Approach: a distribution is fully described by how many balls c_i of each color
 *   go to box 1 (the rest, balls[i]-c_i, go to box 2), subject to sum(c_i) = n.
 *   The number of distinct shuffles realising one split is
 *   (n! / prod c_i!) * (n! / prod (balls[i]-c_i)!) — arrangements of each box's
 *   multiset. The n!*n! factor is identical for every split, so it cancels in the
 *   probability and we only accumulate the "term" prod 1/(c_i! (balls[i]-c_i)!).
 *   DFS over colors choosing c_i, prune when box 1 would exceed n, and at each
 *   complete split with exactly n balls in box 1 add the term to the denominator;
 *   add it to the numerator as well when the two boxes have an equal distinct
 *   count (distinct = number of colors with a positive share in that box). The
 *   answer is numerator / denominator.
 *
 * Complexity: O(prod(balls[i]+1)) splits, at most 7^8 in the worst case but far
 *   fewer after the sum-<= n pruning; each leaf is O(1). O(k) recursion depth.
 */

#include <vector>
using namespace std;

class Solution {
public:
    double getProbability(vector<int>& balls) {
        k = balls.size();
        int total = 0;
        for (int b : balls) total += b;
        n = total / 2;                 // each box must receive exactly n balls

        // Factorials up to the maximum per-color count (6) are all we need, since
        // the shared n!*n! factor was cancelled out of the ratio.
        fact[0] = 1.0;
        for (int i = 1; i <= 6; ++i) fact[i] = fact[i - 1] * i;

        numerator = 0.0;
        denominator = 0.0;
        dfs(balls, 0, 0, 0, 0, 1.0);
        return numerator / denominator;
    }

private:
    int k, n;
    double fact[7];
    double numerator, denominator;

    // i: current color; box1Count: balls already placed in box 1; distinct1 /
    // distinct2: colors with a positive share in box 1 / box 2 so far; term: the
    // running product of 1/(c_j! (b_j-c_j)!) over the colors decided so far.
    void dfs(const vector<int>& balls, int i, int box1Count,
             int distinct1, int distinct2, double term) {
        if (i == k) {
            if (box1Count != n) return;        // box 1 must hold exactly n balls
            denominator += term;
            if (distinct1 == distinct2)         // equal distinct-color counts
                numerator += term;
            return;
        }

        // Try every way to send c balls of color i to box 1 (remainder to box 2).
        for (int c = 0; c <= balls[i]; ++c) {
            if (box1Count + c > n) break;        // overfilling box 1: prune (c grows)

            int d1 = distinct1 + (c > 0 ? 1 : 0);             // color present in box 1?
            int d2 = distinct2 + (c < balls[i] ? 1 : 0);      // color present in box 2?
            dfs(balls, i + 1, box1Count + c, d1, d2,
                term / (fact[c] * fact[balls[i] - c]));
        }
    }
};
