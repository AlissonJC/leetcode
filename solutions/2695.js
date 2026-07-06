/*
 * LeetCode 2695 - Array Wrapper
 *
 * Create a class ArrayWrapper that stores an array of integers passed to its
 * constructor and customizes two coercions:
 *   - Adding two instances with + yields the sum of all elements across both arrays.
 *   - Passing an instance to String() yields the elements as a comma-separated list
 *     wrapped in brackets, e.g. "[1,2,3]".
 *
 * Input  : number[] nums given to the constructor.
 * Output : (obj1 + obj2) is the total of both arrays' elements; String(obj) is the
 *          bracketed comma-separated form of obj's array.
 *
 * Constraints: 0 <= nums.length <= 1000; 0 <= nums[i] <= 1000.
 *
 * Approach: lean on JavaScript's built-in coercion hooks. The + operator turns each
 *   operand into a primitive by calling valueOf, so defining valueOf to return the
 *   array's numeric sum makes obj1 + obj2 evaluate to sum1 + sum2 automatically.
 *   Likewise String(obj) invokes toString, so defining toString to join the elements
 *   with commas inside brackets produces the required "[...]" text. An empty array
 *   sums to 0 and joins to "", giving 0 and "[]" respectively with no special casing.
 *
 * Complexity: constructor O(1) (stores the reference); valueOf O(n) to sum, toString
 *   O(n) to join, n = nums.length. O(1) extra space beyond the stored array.
 */

/**
 * @param {number[]} nums
 * @return {void}
 */
var ArrayWrapper = function(nums) {
    // Keep the numbers; both coercion hooks read from here.
    this.nums = nums;
};

/**
 * @return {number} sum of the wrapped array; the + operator coerces via valueOf
 */
ArrayWrapper.prototype.valueOf = function() {
    // Empty array reduces to the initial 0, so [] + [] === 0 with no special case.
    return this.nums.reduce((total, x) => total + x, 0);
};

/**
 * @return {string} the elements as "[a,b,c]"; String() coerces via toString
 */
ArrayWrapper.prototype.toString = function() {
    // join(",") on an empty array yields "", producing "[]".
    return "[" + this.nums.join(",") + "]";
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = ArrayWrapper;
