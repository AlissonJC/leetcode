/*
 * LeetCode 2634 - Filter Elements from Array
 *
 * Given an integer array arr and a predicate fn, return a new array containing only the
 * elements of arr for which fn evaluates to a truthy value. fn is called as fn(arr[i], i)
 * -- it receives both the element and its index, and may use either. "Truthy" means
 * Boolean(fn(arr[i], i)) === true. Must be solved WITHOUT the built-in Array.filter.
 *
 * Input  : arr (integers), fn (element, index) -> value tested for truthiness.
 * Output : a new array of the kept elements, in their original order.
 *
 * Constraints: 0 <= arr.length <= 1000; -1e9 <= arr[i] <= 1e9.
 *
 * Approach: walk arr by index, and for each position evaluate fn(arr[i], i). Placing that
 *   call directly in an `if` condition applies JavaScript's truthiness coercion, so any
 *   truthy result (a non-zero number, a non-empty string, an object, true) keeps the
 *   element while any falsy result (0, "", null, undefined, NaN, false) drops it -- there
 *   is no need to compare against true. Push the ORIGINAL arr[i] (not fn's return value)
 *   to preserve both the element and its order. Passing i as the second argument lets
 *   index-aware predicates work.
 *
 * Complexity: O(n) time for one pass and O(k) space for the k kept elements.
 */

/**
 * @param {number[]} arr
 * @param {Function} fn   (element, index) -> value; element is kept when this is truthy
 * @return {number[]}
 */
var filter = function (arr, fn) {
    const filtered = [];

    for (let i = 0; i < arr.length; i++) {
        // The `if` coerces fn's result to Boolean, so falsy returns (0, "", null, ...)
        // exclude the element. Keep the original arr[i], not the predicate's value.
        if (fn(arr[i], i)) {
            filtered.push(arr[i]);
        }
    }

    return filtered;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = filter;
