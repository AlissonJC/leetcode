/*
 * LeetCode 2623 - Memoize
 *
 * Given a function fn, return a memoized version of it. The memoized function must
 * never invoke fn twice for the same arguments: on a repeated argument list it returns
 * the previously computed (cached) result instead of calling fn again. The target
 * functions take integer arguments -- sum(a, b), fib(n), factorial(n). Argument order
 * is significant: for sum, the calls (a, b) and (b, a) with a != b are considered
 * different and must each trigger their own computation.
 *
 * Input  : Function fn.
 * Output : a function with fn's signature that caches results per distinct argument
 *          list; each unique argument list calls fn exactly once.
 *
 * Constraints: 1 <= a, b <= 1e5; 1 <= n <= 10; at most 1e5 total and 1e5 unique calls.
 *
 * Approach: capture a private Map in a closure. For every call, turn the full argument
 *   list into a cache key with JSON.stringify(args). Serializing the array preserves
 *   argument ORDER and ARITY, so "[2,3]" and "[3,2]" are different keys (satisfying the
 *   sum requirement) and a one-argument call can never collide with a two-argument one.
 *   If the key is already in the Map, return the stored value untouched -- fn is not
 *   called, which is the whole point of memoization. Otherwise compute fn(...args),
 *   cache it under the key, and return it.
 *
 * Complexity: O(L) per call to build the key from L arguments (here L is 1 or 2) plus
 *   O(1) Map lookup/insert. Space is O(u) for u distinct argument lists seen.
 */

/**
 * @param {Function} fn
 * @return {Function} a memoized version of fn
 */
function memoize(fn) {
    // Private per-memoization cache: serialized-args string -> computed result.
    const cache = new Map();

    return function(...args) {
        // Order- and arity-preserving key. "[2,3]" != "[3,2]" and "[5]" != "[5,0]".
        const key = JSON.stringify(args);

        // Cache hit: hand back the stored value WITHOUT calling fn again.
        if (cache.has(key)) {
            return cache.get(key);
        }

        // Cache miss: compute once, remember it, and return it.
        const result = fn(...args);
        cache.set(key, result);
        return result;
    };
}

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = memoize;
