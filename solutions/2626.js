/*
 * LeetCode 2626 - Array Reduce Transformation
 *
 * Given an integer array nums, a reducer function fn, and an initial value init,
 * return the single value produced by folding fn across nums left to right:
 *   val = fn(init, nums[0]); val = fn(val, nums[1]); ... and so on.
 * The accumulated val after the last element is the answer. An empty array yields
 * init. Must be solved WITHOUT the built-in Array.prototype.reduce.
 *
 * Input  : nums (integers), fn (accumulator, current) -> value, init (seed value).
 * Output : the final accumulated value.
 *
 * Constraints: 0 <= nums.length <= 1000; 0 <= nums[i] <= 1000; 0 <= init <= 1000.
 *
 * Approach: this is a hand-written left fold. Start the accumulator at init, then walk
 *   the array in order, replacing the accumulator with fn(accumulator, nums[i]) at each
 *   step. Returning after the loop gives the fully reduced value; if nums is empty the
 *   loop never executes, so init is returned unchanged -- exactly the required empty
 *   behavior with no special case needed.
 *
 * Complexity: O(n) time for one pass over nums and O(1) extra space.
 */

/**
 * @param {number[]} nums
 * @param {Function} fn    reducer: (accumulator, currentValue) -> nextAccumulator
 * @param {number} init    initial accumulator value
 * @return {number}
 */
var reduce = function (nums, fn, init) {
    // Seed the accumulator; an empty nums leaves this as init (the loop is skipped).
    let val = init;

    // Fold left to right: each element updates the accumulator via fn.
    for (let i = 0; i < nums.length; i++) {
        val = fn(val, nums[i]);
    }

    return val;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = reduce;
