/*
 * LeetCode 2667 - Create Hello World Function
 *
 * Write a function createHelloWorld that returns a new function. That returned
 * function must always produce the string "Hello World", no matter what (or how
 * many) arguments are passed to it.
 *
 * Input  : none to createHelloWorld itself; the returned function may receive any
 *          arguments (0..10 of them), which are ignored.
 * Output : a function that returns the constant string "Hello World" on every call.
 *
 * Constraints: 0 <= args.length <= 10.
 *
 * Approach: return a closure whose body ignores its parameters entirely and hands
 *   back the literal "Hello World". Collecting the arguments with a rest parameter
 *   makes it explicit that any inputs are accepted and simply discarded, which is
 *   exactly the required behavior.
 *
 * Complexity: O(1) time and O(1) space per call -- it just returns a constant.
 */

/**
 * @return {Function} a function that always returns the string "Hello World"
 */
var createHelloWorld = function() {
    // The rest parameter swallows any and all arguments; they are never used.
    return function(...args) {
        return "Hello World";
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = createHelloWorld;
