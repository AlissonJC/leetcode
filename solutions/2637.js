/*
 * LeetCode 2637 - Promise Time Limit
 *
 * Given an asynchronous function fn and a time budget t (milliseconds), return a
 * time-limited version of fn. The returned function forwards its arguments to fn and:
 *   - if fn settles (resolves or rejects) within t ms, adopts that outcome;
 *   - if fn is still pending after t ms, rejects with the string "Time Limit Exceeded".
 *
 * Input  : fn (async function), t (deadline in ms). The wrapper's own arguments are
 *          passed straight through to fn.
 * Output : a function returning a Promise governed by the deadline above.
 *
 * Constraints: 0 <= inputs.length <= 10; 0 <= t <= 1000; fn returns a Promise.
 *
 * Approach: wrap the work in a new Promise and start a timer that rejects with
 *   "Time Limit Exceeded" after t ms. Kick off fn(...args) and forward its settlement
 *   with .then(resolve, reject); whichever settles first -- fn or the timer -- wins,
 *   because a promise can only settle once, so the later one is a harmless no-op. A
 *   .finally clears the timer once fn settles so a fast call leaves no dangling timeout.
 *   Attaching reject as fn's rejection handler also means a LATE fn failure arriving
 *   after a timeout is still consumed, avoiding an unhandled-rejection warning. Invoking
 *   fn inside the executor additionally turns any synchronous throw into a rejection.
 *
 * Complexity: O(1) overhead beyond fn's own running time and one pending timer.
 */

/**
 * @param {Function} fn   async function whose result is subject to the deadline
 * @param {number} t      time limit in milliseconds
 * @return {Function}
 */
var timeLimit = function (fn, t) {
    return function (...args) {
        return new Promise((resolve, reject) => {
            // Deadline: if fn has not settled in t ms, reject the wrapper.
            const timer = setTimeout(() => reject("Time Limit Exceeded"), t);

            // Run fn and race it against the timer. The first settlement wins; the
            // finally cancels the timer, and the rejection handler swallows any late
            // fn failure that arrives after a timeout has already been reported.
            fn(...args)
                .then(resolve, reject)
                .finally(() => clearTimeout(timer));
        });
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = timeLimit;
