/*
 * LeetCode 2620 - Counter
 *
 * Given an integer n, return a "counter" function. The first time that returned
 * function is called it yields n; every subsequent call yields one more than the
 * previous result (n, n + 1, n + 2, ...).
 *
 * Input  : number n -- the starting value of the counter.
 * Output : a zero-argument function that returns the next number in the sequence
 *          each time it is invoked.
 *
 * Constraints: -1000 <= n <= 1000; the counter may be called 0..1000 times.
 *
 * Approach: use a closure. The inner function captures the variable n from the
 *   surrounding createCounter scope, so n survives between calls as private, mutable
 *   state belonging to this one counter. Returning n++ (post-increment) hands back
 *   the current value and only then increases it -- so the first call returns the
 *   original n and each later call returns one more, exactly as required. Because a
 *   new n binding is created on every createCounter call, separate counters are fully
 *   independent and never share state.
 *
 * Complexity: O(1) time per call and O(1) space (a single captured integer).
 */

/**
 * @param {number} n
 * @return {Function} a counter that returns n, then n+1, n+2, ... on each call
 */
var createCounter = function(n) {
    // The returned closure owns its own `n`. Post-increment yields the current value
    // first, then advances it for the next invocation.
    return function() {
        return n++;
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = createCounter;
