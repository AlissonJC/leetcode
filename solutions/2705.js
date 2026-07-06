/*
 * LeetCode 2705 - Compact Object
 *
 * Given a value obj that is the result of JSON.parse (so a valid JSON object, array,
 * or primitive), return a "compact" copy: every key whose value is falsy is removed,
 * recursively, throughout the structure. Arrays count as objects keyed by index, and
 * removing falsy elements re-densifies the array (the survivors keep their order but
 * are re-indexed). A value is falsy exactly when Boolean(value) is false, i.e. one of
 * false, 0, "", null, undefined, NaN.
 *
 * Input  : Object|Array obj (valid JSON, 2 <= JSON.stringify(obj).length <= 1e6).
 * Output : the same shape with all falsy-valued keys/elements dropped at every level.
 *
 * Approach: recurse. Primitives (and null) have no keys to filter, so return them
 *   unchanged -- this is the base case. For an array, walk the elements and keep only
 *   the truthy ones, pushing the recursively compacted form of each survivor; because
 *   we push (never leave holes), the result is dense. For a plain object, keep only
 *   the entries whose value is truthy, storing the compacted value. The falsiness test
 *   is applied to the ORIGINAL value: arrays and objects are always truthy, so a
 *   nested container is retained even when it compacts down to [] or {} (see example 3
 *   where [0] becomes [] but stays). Each node is visited once.
 *
 * Complexity: O(n) time and O(n) space over the n nodes of the structure; recursion
 *   depth equals the nesting depth.
 */

/**
 * @param {Object|Array} obj
 * @return {Object|Array}
 */
var compactObject = function(obj) {
    // Base case: primitives (numbers, strings, booleans) and null have no keys to
    // compact, so they pass straight through. typeof null is "object", hence the
    // explicit null guard.
    if (obj === null || typeof obj !== "object") {
        return obj;
    }

    // Arrays: keep truthy elements only, re-densifying (push, never leave gaps).
    if (Array.isArray(obj)) {
        const compacted = [];
        for (const item of obj) {
            if (item) {                     // drop falsy elements (null, 0, false, "")
                compacted.push(compactObject(item));
            }
        }
        return compacted;
    }

    // Plain objects: keep entries whose value is truthy, compacting each kept value.
    const compacted = {};
    for (const key of Object.keys(obj)) {
        const value = obj[key];
        if (value) {                        // drop keys mapping to a falsy value
            compacted[key] = compactObject(value);
        }
    }
    return compacted;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = compactObject;
