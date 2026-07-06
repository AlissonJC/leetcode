/*
 * LeetCode 2724 - Sort By
 *
 * Given an array arr and a function fn that maps each element to a number, return the
 * array sorted in ascending order by fn's output. fn always returns a number, and for
 * a given array it never produces the same number for two elements (keys are unique).
 *
 * Input  : Array arr, Function fn (element -> number sort key).
 * Output : a new array with arr's elements ordered by ascending fn(element).
 *
 * Constraints: 1 <= arr.length <= 5 * 1e5.
 *
 * Approach: sort with a numeric comparator that subtracts the two keys,
 *   (a, b) => fn(a) - fn(b). A negative result orders a before b, so this yields
 *   ascending order and handles negative keys correctly -- unlike Array.sort with no
 *   comparator, which coerces elements to strings and would misorder numbers. Sort a
 *   shallow copy ([...arr]) so the caller's array is left untouched. Keys are unique,
 *   so tie-breaking/stability never comes into play.
 *
 * Complexity: O(n log n) comparisons for n = arr.length; O(n) space for the copy.
 */

/**
 * @param {Array} arr
 * @param {Function} fn
 * @return {Array}
 */
var sortBy = function(arr, fn) {
    // Copy first so the input isn't mutated; subtract keys for ascending numeric order.
    return [...arr].sort((a, b) => fn(a) - fn(b));
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = sortBy;
