/*
 * LeetCode 2635 - Apply Transform Over Each Element in Array
 *
 * Given an integer array arr and a mapping function fn, return a NEW array where each
 * position holds the transformed value: returnedArray[i] === fn(arr[i], i). fn receives
 * both the element and its index, so transforms may depend on position. The original
 * array must not be modified. Must be solved WITHOUT the built-in Array.map.
 *
 * Input  : arr (integers), fn (element, index) -> number.
 * Output : a new array of the transformed values, same length as arr.
 *
 * Constraints: 0 <= arr.length <= 1000; -1e9 <= arr[i] <= 1e9; fn returns a number.
 *
 * Approach: allocate a fresh result array of the same length and fill slot i with
 *   fn(arr[i], i) in a single linear pass. Writing into a brand-new array (rather than
 *   assigning back into arr) keeps the input untouched, and indexing result[i] directly
 *   mirrors the required returnedArray[i] === fn(arr[i], i) contract. Passing i as the
 *   second argument lets position-aware mappers work; mappers that ignore it still work
 *   because extra arguments are simply unused.
 *
 * Complexity: O(n) time for one pass and O(n) space for the returned array.
 */

/**
 * @param {number[]} arr
 * @param {Function} fn   (element, index) -> transformed number
 * @return {number[]}
 */
var map = function (arr, fn) {
    // New array of matching length so the input arr is never mutated.
    const result = new Array(arr.length);

    for (let i = 0; i < arr.length; i++) {
        result[i] = fn(arr[i], i);   // exactly the returnedArray[i] = fn(arr[i], i) rule
    }

    return result;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = map;
