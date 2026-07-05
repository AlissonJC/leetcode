/*
 * LeetCode 2648 - Generate Fibonacci Sequence
 *
 * Write a generator function that returns a generator yielding the Fibonacci sequence
 * 0, 1, 1, 2, 3, 5, 8, 13, ... where each term is the sum of the two before it
 * (Xn = Xn-1 + Xn-2, seeded with X0 = 0, X1 = 1). The caller pulls terms one at a time
 * via the generator's next() method; the i-th next() call returns the i-th term.
 *
 * Input  : none to the generator itself; the consumer decides how many terms to pull.
 * Output : successive Fibonacci numbers, one per next() call (value 0 first).
 *
 * Constraints: the harness requests 0 <= callCount <= 50 terms.
 *
 * Approach: use a generator (function*) that carries the running pair a = current term
 *   and b = next term, starting at (0, 1). Each iteration yields a, which suspends the
 *   generator until the next next() call, then advances the pair to (b, a + b) so the
 *   following resume yields the subsequent term. The unbounded while (true) loop is safe
 *   because generators are lazy: no term is computed until it is requested, so the
 *   consumer -- not the generator -- controls how far the sequence runs.
 *
 * Complexity: O(1) time and space per next() call. For up to 50 terms the largest value
 *   is Fib(49) = 7778742049, comfortably within Number.MAX_SAFE_INTEGER, so ordinary
 *   number arithmetic stays exact and no BigInt is required.
 */

/**
 * @return {Generator<number>}
 */
var fibGenerator = function* () {
    // a is the term about to be yielded; b is the term after it.
    let a = 0;
    let b = 1;

    while (true) {
        yield a;                 // hand back the current term and pause here
        [a, b] = [b, a + b];     // slide the window forward for the next resume
    }
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = fibGenerator;
