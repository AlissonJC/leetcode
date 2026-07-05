/*
 * LeetCode 2625 - Flatten Deeply Nested Array
 *
 * A multi-dimensional array holds integers and/or other multi-dimensional arrays.
 * Given such an array arr and a depth n, return a flattened copy in which a sub-array
 * is replaced by its elements ONLY while the current nesting depth is less than n.
 * Elements of the outermost array sit at depth 0, their sub-arrays' elements at depth
 * 1, and so on. Must be solved WITHOUT the built-in Array.prototype.flat.
 *
 * Input  : arr (nested array of integers), n (how many levels deep to flatten).
 * Output : the flattened array; with n = 0 the original structure is returned intact.
 *
 * Constraints: up to ~1e5 integers and ~1e5 sub-arrays; maximum nesting depth <= 1000;
 *   0 <= n <= 1000.
 *
 * Approach: a depth-first walk that carries the current depth and appends into one
 *   shared result array. For each element: if it is an array AND depth < n, recurse
 *   into it at depth + 1 so its contents are pulled up a level; otherwise append the
 *   element as-is (a plain integer, or a sub-array that has reached the depth cutoff).
 *   Two details matter. First, membership is tested with Array.isArray, never
 *   truthiness -- a value like 0 must count as an element, not a container. Second, the
 *   result is threaded through the recursion and items are pushed one at a time rather
 *   than doing result.push(...flatten(sub)): spreading a sub-array that can hold ~1e5
 *   elements into function arguments risks exceeding the engine's argument-count limit.
 *   With max depth 1000 the recursion stays well inside the call-stack limit.
 *
 * Complexity: O(N) time where N is the total number of integers and sub-arrays visited,
 *   and O(N) space for the output plus O(depth) recursion stack.
 */

/**
 * @param {any[]} arr   the multi-dimensional array to flatten
 * @param {number} n    number of nesting levels to flatten (depth 0 is the top level)
 * @return {any[]}
 */
var flat = function (arr, n) {
    const result = [];

    // Append the elements of `subArr` (currently at nesting depth `depth`) into result,
    // flattening any child array while we are still shallower than n.
    const walk = (subArr, depth) => {
        for (const item of subArr) {
            if (Array.isArray(item) && depth < n) {
                walk(item, depth + 1);   // depth < n: dissolve this sub-array one level
            } else {
                result.push(item);       // integer, or an array kept at the depth cutoff
            }
        }
    };

    walk(arr, 0);
    return result;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = flat;
