/*
 * LeetCode 2727 - Is Object Empty
 *
 * Given an object or array (the output of JSON.parse), return whether it is empty: an
 * object with no key-value pairs, or an array with no elements.
 *
 * Input  : Object|Array obj.
 * Output : boolean -- true if it has no own enumerable keys/elements, else false.
 *
 * Constraints: 2 <= JSON.stringify(obj).length <= 1e5. Bonus: solve in O(1).
 *
 * Approach: loop over the keys with for...in and return false the instant one appears;
 *   if the loop body never runs, there are no keys/indices, so return true. Because it
 *   short-circuits on the first property, this is O(1) -- unlike Object.keys(obj).length
 *   === 0, which first builds an array of every key (O(n)). For arrays, for...in visits
 *   the numeric indices, so a non-empty array exits on index "0" and an empty one falls
 *   through to true.
 *
 * Complexity: O(1) time (stops at the first key) and O(1) space.
 */

/**
 * @param {Object|Array} obj
 * @return {boolean}
 */
var isEmpty = function(obj) {
    // The presence of even one enumerable key/index means it is not empty.
    for (const _key in obj) {
        return false;
    }
    // Loop never executed -> no keys/elements -> empty.
    return true;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = isEmpty;
