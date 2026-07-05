/*
 * LeetCode 2621 - Sleep
 *
 * Given a positive integer millis, return a promise that resolves after millis
 * milliseconds have elapsed. The value it resolves with does not matter -- callers
 * only care that the delay has passed before the promise settles.
 *
 * Input  : number millis -- how long to wait, in milliseconds.
 * Output : a Promise that resolves once millis milliseconds have gone by.
 *
 * Constraints: 1 <= millis <= 1000.
 *
 * Approach: the browser/Node timer API setTimeout(cb, millis) invokes cb after at
 *   least millis milliseconds, but it is callback-based, not awaitable. Wrapping it
 *   in `new Promise(resolve => setTimeout(resolve, millis))` hands setTimeout the
 *   promise's own resolve function as that callback, so the promise settles exactly
 *   when the timer fires. That converts the one-shot timer into a thenable the caller
 *   can await or chain .then() onto. The function is async only to match the expected
 *   signature; the returned timer-promise carries the actual delay.
 *
 * Complexity: O(1) work; the cost is millis milliseconds of wall-clock waiting, not
 *   CPU time -- the event loop is free to do other work while the timer pends.
 */

/**
 * @param {number} millis
 * @return {Promise}
 */
async function sleep(millis) {
    // setTimeout schedules `resolve` to run after `millis` ms, so the promise settles
    // then. Awaiting/chaining this promise is what "sleeping" reduces to.
    return new Promise(resolve => setTimeout(resolve, millis));
}

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = sleep;
