/*
 * LeetCode 2627 - Debounce
 *
 * Given a function fn and a delay t (milliseconds), return a debounced version of fn.
 * A debounced function postpones running fn until t milliseconds have passed since the
 * MOST RECENT invocation: if it is called again before that window elapses, the pending
 * run is cancelled and the clock restarts. When fn finally runs, it receives the
 * arguments from the latest call that triggered it.
 *
 * Input  : fn (the function to debounce), t (quiet-period length in ms).
 * Output : a function that forwards its arguments to fn, but only after t ms of quiet.
 *
 * Constraints: 0 <= t <= 1000; 0 <= number of calls <= 10.
 *
 * Approach: keep a single pending-timer handle in a closure. On every call, first
 *   clearTimeout(timer) to abort whatever run was previously scheduled, then start a
 *   fresh setTimeout(() => fn(...args), t). Because each call cancels the one before it,
 *   only a call that is NOT followed by another within t ms ever reaches its timeout and
 *   executes -- and it does so with its own captured args. clearTimeout on an undefined
 *   or already-fired handle is a safe no-op, so the very first call needs no guard.
 *
 * Complexity: O(1) time and space per call (one timer handle, constant work).
 */

/**
 * @param {Function} fn
 * @param {number} t  debounce delay in milliseconds
 * @return {Function}
 */
var debounce = function (fn, t) {
    // Handle of the currently pending fn execution; undefined when nothing is scheduled.
    let timer;

    return function (...args) {
        // Cancel any run still waiting from an earlier call within this window...
        clearTimeout(timer);
        // ...and (re)schedule fn to run t ms from now with THIS call's arguments.
        timer = setTimeout(() => fn(...args), t);
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = debounce;
