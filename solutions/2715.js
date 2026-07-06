/*
 * LeetCode 2715 - Timeout Cancellation
 *
 * Given a function fn, its argument list args, and a delay t (ms), schedule fn to run
 * with those arguments after t milliseconds and return a cancel function. If the cancel
 * function is called before t ms elapse, the pending execution of fn is cancelled and
 * fn never runs; otherwise fn runs at t ms as scheduled and a later cancel does nothing.
 *
 * Input  : Function fn, Array args, number t (delay in ms).
 * Output : a zero-argument cancel function that aborts the pending fn call if invoked
 *          before the delay expires.
 *
 * Constraints: 1 <= args.length <= 10; 20 <= t <= 1000; 10 <= cancelTimeMs <= 1000.
 *
 * Approach: this maps directly onto the timer API. setTimeout(() => fn(...args), t)
 *   queues fn to fire after t ms and hands back a timer handle. Return a closure that
 *   calls clearTimeout(handle): if it runs before the timer fires, the callback is
 *   removed from the queue and fn is never called; if it runs after fn has already
 *   fired, clearTimeout on an elapsed timer is a harmless no-op.
 *
 * Complexity: O(1) time and space to register the timer and the canceller (excluding
 *   fn's own runtime when it eventually executes).
 */

/**
 * @param {Function} fn
 * @param {Array} args
 * @param {number} t
 * @return {Function} cancel function that aborts the pending fn call
 */
var cancellable = function(fn, args, t) {
    // Queue fn to run once, t ms from now, with the provided arguments.
    const timer = setTimeout(() => fn(...args), t);

    // Cancelling clears the pending timer; harmless if fn has already fired.
    return () => clearTimeout(timer);
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = cancellable;
