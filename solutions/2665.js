/*
 * LeetCode 2665 - Counter II
 *
 * Write a function createCounter that accepts an initial integer init and returns
 * an object exposing three methods. increment() adds 1 to the current value and
 * returns the new value; decrement() subtracts 1 and returns the new value;
 * reset() restores the current value back to the original init and returns it.
 *
 * Input  : number init -- the starting value, and also the value reset() returns to.
 * Output : an object { increment, decrement, reset }, each a zero-argument function
 *          returning the counter's value after applying its operation.
 *
 * Constraints: -1000 <= init <= 1000; 0 <= calls.length <= 1000; each call is one
 *   of "increment", "decrement", "reset".
 *
 * Approach: use a closure. A local variable `current` holds the live value while
 *   the parameter `init` stays untouched as the fixed reset target -- both are
 *   captured privately by createCounter's scope, so they persist between method
 *   calls and are not shared across separate counters. increment/decrement mutate
 *   `current` with pre-increment/decrement (change first, then return the result);
 *   reset copies `init` back into `current`. Since `init` is never reassigned,
 *   reset always returns to the true original even after many operations.
 *
 * Complexity: O(1) time per method call and O(1) space (two captured integers).
 */

/**
 * @param {integer} init
 * @return {{ increment: Function, decrement: Function, reset: Function }}
 */
var createCounter = function(init) {
    // Private live value; `init` remains the immutable reset target in this scope.
    let current = init;
    return {
        // Pre-increment/decrement so the updated value is what gets returned.
        increment: () => ++current,
        decrement: () => --current,
        // Restore to the captured original, then return it.
        reset: () => (current = init),
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = createCounter;
