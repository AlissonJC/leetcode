/*
 * LeetCode 2703 - Return Length of Arguments Passed
 *
 * Write a function argumentsLength that returns how many arguments it was called
 * with, regardless of their types.
 *
 * Input  : any number of arguments (0..100) of any type.
 * Output : number -- the count of arguments received.
 *
 * Constraints: 0 <= args.length <= 100.
 *
 * Approach: gather every argument into an array with a rest parameter (...args) and
 *   return its length. The rest parameter captures the full argument list by count,
 *   so this works for zero arguments (length 0) up through the maximum, with no
 *   dependence on argument types.
 *
 * Complexity: O(n) to collect n arguments and O(n) space for the rest array; the
 *   length read itself is O(1).
 */

/**
 * @param {...(null|boolean|number|string|Array|Object)} args
 * @return {number} count of arguments passed
 */
var argumentsLength = function(...args) {
    // Rest parameter collects all passed arguments; its length is the count.
    return args.length;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = argumentsLength;
