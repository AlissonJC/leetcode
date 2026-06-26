/*
 * LeetCode 470 - Implement Rand10() Using Rand7()
 *
 * Given rand7(), which returns a uniform random integer in [1, 7], implement
 * rand10() returning a uniform random integer in [1, 10], using only rand7() as
 * the source of randomness (no language RNG).
 *
 * Input  : none (rand7() is the provided oracle). Output : int — uniform in [1,10].
 *
 * Constraints: rand10() is invoked up to n <= 10^5 times per test. Each result
 *   must be independent and uniformly distributed over [1, 10].
 *
 * Approach: rejection sampling. Two independent rand7() draws form the pair
 *   (row, col), and idx = (row - 1) * 7 + col is uniform over [1, 49] because the
 *   49 (row, col) pairs are equally likely. Keep only idx in [1, 40] — 40 is the
 *   largest multiple of 10 that fits — and map it to [1, 10] via (idx - 1) % 10 + 1,
 *   which is exactly uniform since each of the 10 residues is hit by 4 of the 40
 *   accepted values. Values 41..49 are discarded and the draw is retried; biasing
 *   never happens because rejection treats every surviving value identically.
 *
 * Complexity: expected O(1) per call — acceptance probability 40/49, so the
 *   expected number of rand7() calls is 2 * 49/40 = 2.45. O(1) space.
 */

// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7
int rand7();

class Solution {
public:
    int rand10() {
        // Retry until the uniform [1,49] draw lands in the accepted [1,40] window.
        while (true) {
            int row = rand7();                  // 1..7
            int col = rand7();                   // 1..7
            int idx = (row - 1) * 7 + col;        // 1..49, each value equally likely

            if (idx <= 40)
                return (idx - 1) % 10 + 1;        // fold 40 values evenly onto 1..10

            // idx in 41..49: reject and draw again (keeps the result unbiased).
        }
    }
};
