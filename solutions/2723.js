/*
 * LeetCode 2723 - Add Two Promises
 *
 * Given two promises that each resolve to a number, return a new promise that
 * resolves to the sum of those two numbers.
 *
 * Input  : Promise promise1, Promise promise2 -- each resolves with a number.
 * Output : Promise<number> that resolves with promise1's value + promise2's value.
 *
 * Constraints: both inputs are promises that resolve with a number.
 *
 * Approach: declare the function async so it implicitly returns a promise. Await both
 *   inputs together with Promise.all -- they are already in flight, so this waits for
 *   the later of the two -- destructure the resolved pair, and return their sum. An
 *   async function wraps the returned number in a resolved promise, matching the
 *   required signature.
 *
 * Complexity: O(1) work; wall-clock is the slower of the two promises (they settle
 *   concurrently), plus the constant-time addition.
 */

/**
 * @param {Promise} promise1
 * @param {Promise} promise2
 * @return {Promise<number>}
 */
var addTwoPromises = async function(promise1, promise2) {
    // Wait for both resolved values, then hand back their sum (auto-wrapped in a promise).
    const [a, b] = await Promise.all([promise1, promise2]);
    return a + b;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = addTwoPromises;
