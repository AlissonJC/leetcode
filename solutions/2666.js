/*
 * LeetCode 2666 - Allow One Function Call
 *
 * Given a function fn, return a new function that behaves like fn but guarantees
 * fn runs at most once. The first invocation of the returned function calls fn with
 * whatever arguments it received and returns fn's result; every later invocation
 * returns undefined and does not call fn at all.
 *
 * Input  : Function fn -- the function to guard.
 * Output : a wrapper function that forwards its arguments to fn on the first call
 *          only, returning fn's result then and undefined thereafter.
 *
 * Constraints: 1 <= calls.length <= 10; 1 <= calls[i].length <= 100;
 *   2 <= JSON.stringify(calls).length <= 1000.
 *
 * Approach: use a closure holding a private boolean `called`, initially false. The
 *   returned function checks the flag: on the first call it flips `called` to true,
 *   invokes fn (forwarding both `this` and the argument list via apply), and returns
 *   the result. On any subsequent call the flag is already true, so it short-circuits
 *   and returns undefined without touching fn. The flag lives in the closure, so it
 *   persists across calls and each once(...) wrapper tracks its own independent state.
 *
 * Complexity: O(1) time per call (a single boolean test) plus the cost of fn itself
 *   on the one call that runs it; O(1) extra space for the captured flag.
 */

/**
 * @param {Function} fn
 * @return {Function}
 */
var once = function(fn) {
    // Private one-shot latch: true once fn has been consumed.
    let called = false;
    return function (...args) {
        if (called) return undefined;   // already spent -> never call fn again
        called = true;                  // latch before invoking, so fn runs exactly once
        // apply forwards the caller's `this` and the spread arguments faithfully.
        return fn.apply(this, args);
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = once;
