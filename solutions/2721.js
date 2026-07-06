/*
 * LeetCode 2721 - Execute Asynchronous Functions in Parallel
 *
 * Given an array of async functions (each takes no arguments and returns a promise),
 * return a single promise that runs them all in parallel -- a hand-rolled Promise.all
 * (which may not be used). The returned promise resolves with an array of every
 * resolved value, in the SAME order as the input functions, once all have resolved;
 * it rejects with the reason of the first function to reject, as soon as that happens.
 *
 * Input  : Array<Function> functions, each returning a Promise.
 * Output : Promise<any[]> resolving to the ordered results, or rejecting with the
 *          first rejection reason.
 *
 * Constraints: 1 <= functions.length <= 10.
 *
 * Approach: wrap everything in one new Promise. Invoke every function synchronously in
 *   a single pass so all their promises are in flight at once (parallel). For each
 *   index i, attach handlers: on success store the value at results[i] -- keyed by the
 *   original index, so the arrival order of results never reorders the output -- and
 *   decrement a remaining counter, resolving with results only when it reaches zero.
 *   On failure, reject immediately with that reason; because a promise can settle just
 *   once, the first rejection wins and any later settle attempts are silently ignored.
 *
 * Complexity: O(n) to launch the n functions and O(n) space for the results array;
 *   wall-clock time is the slowest promise (they run concurrently), not their sum.
 */

/**
 * @param {Array<Function>} functions
 * @return {Promise<any>}
 */
var promiseAll = function(functions) {
    return new Promise((resolve, reject) => {
        const n = functions.length;
        const results = new Array(n);
        let remaining = n;                 // how many promises are still pending

        functions.forEach((fn, i) => {
            // Start every promise now (synchronous loop) => true parallel execution.
            fn().then(
                (value) => {
                    results[i] = value;    // store by original index to preserve order
                    remaining--;
                    if (remaining === 0) {
                        resolve(results);  // all done -> resolve with ordered results
                    }
                },
                (reason) => {
                    reject(reason);        // first rejection settles; later ones no-op
                }
            );
        });
    });
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = promiseAll;
