/*
 * LeetCode 2619 - Array Prototype Last
 *
 * Enhance every array so that calling arr.last() returns its final element. When the
 * array is empty, last() must return -1 instead. The method is added directly to
 * Array.prototype so it is available on all arrays.
 *
 * Input  : none explicitly -- `this` is the array the method is invoked on.
 * Output : the last element of the array, or -1 if the array has no elements.
 *
 * Approach: read this.length once. If it is non-zero, index the final slot at
 *   this[this.length - 1]; otherwise the array is empty, so return -1. The check is
 *   deliberately on the LENGTH, not on the truthiness of the last element: values
 *   like 0, false, null, "", NaN, or undefined are perfectly valid last elements and
 *   must be returned as-is. A shortcut such as `this.at(-1) || -1` would wrongly turn
 *   any falsy last element into -1, so it is avoided here.
 *
 * Complexity: O(1) time and O(1) space -- a single length read and one index.
 */

/**
 * @return {null|boolean|number|string|Array|Object} the last element, or -1 if empty
 */
Array.prototype.last = function() {
    // Non-empty -> hand back the final slot; empty -> the sentinel -1.
    // Gate on length so a falsy last element (0, false, "", null, ...) still returns.
    return this.length ? this[this.length - 1] : -1;
};
