/*
 * LeetCode 2725 - Interval Cancellation
 *
 * Given a function fn, its argument list args, and an interval t (ms), call fn with
 * those arguments immediately, then keep calling it every t milliseconds, and return
 * a cancel function. When the cancel function is invoked (the harness schedules it via
 * setTimeout at cancelTimeMs), the repeating calls stop.
 *
 * Input  : Function fn, Array args, number t (interval in ms).
 * Output : a zero-argument cancel function that halts the repeating fn calls.
 *
 * Constraints: 1 <= args.length <= 10; 30 <= t <= 100; 10 <= cancelTimeMs <= 500.
 *
 * Approach: run fn(...args) once right away so the first call lands at time 0, then
 *   register setInterval(() => fn(...args), t) to fire it every t ms thereafter. Return
 *   a closure that calls clearInterval on that handle, which stops all future ticks.
 *   Only calls whose scheduled time is strictly before cancelTimeMs actually run, since
 *   clearInterval removes the interval before the next tick would fire.
 *
 * Complexity: O(1) to set up the immediate call, the interval, and the canceller
 *   (excluding fn's own per-call runtime).
 */

/**
 * @param {Function} fn
 * @param {Array} args
 * @param {number} t
 * @return {Function} cancel function that stops the repeating calls
 */
var cancellable = function(fn, args, t) {
    // First call happens immediately, at time 0.
    fn(...args);

    // Subsequent calls every t ms until cancelled.
    const timer = setInterval(() => fn(...args), t);

    // Cancelling clears the interval, preventing any further ticks.
    return () => clearInterval(timer);
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = cancellable;
