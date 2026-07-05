/*
 * LeetCode 2629 - Function Composition
 *
 * Given an array of single-argument functions [f1, f2, ..., fn], return their function
 * composition: a new function that, given x, computes f1(f2(...fn(x)...)). In other
 * words the functions are applied from RIGHT to LEFT -- the last one runs first on x,
 * and each result feeds the function to its left. Composing an empty array yields the
 * identity function, f(x) = x.
 *
 * Input  : functions (array of Number -> Number functions).
 * Output : a function that maps x to the right-to-left composition of all of them.
 *
 * Constraints: -1000 <= x <= 1000; 0 <= functions.length <= 1000; each function takes
 *   and returns a single integer.
 *
 * Approach: return a closure over the functions array. When called with x, seed an
 *   accumulator with x and walk the array from the last index down to the first,
 *   replacing the accumulator with functions[i](accumulator) each step. Iterating in
 *   decreasing index order is exactly the right-to-left evaluation the composition
 *   requires. If the array is empty the loop never runs and x is returned unchanged --
 *   the identity case, handled with no special branch.
 *
 * Complexity: O(n) time per call for n functions, and O(1) extra space (plus the
 *   closure over the functions array).
 */

/**
 * @param {Function[]} functions
 * @return {Function} x -> f1(f2(...fn(x)...))
 */
var compose = function (functions) {
    return function (x) {
        // Seed with x, then apply functions right-to-left (last index first).
        let result = x;
        for (let i = functions.length - 1; i >= 0; i--) {
            result = functions[i](result);
        }
        return result;   // empty array -> loop skipped -> identity (returns x)
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = compose;
