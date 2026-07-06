/*
 * LeetCode 2677 - Chunk Array
 *
 * Given an array arr and a positive chunk size, return a "chunked" array: the
 * original elements in order, grouped into consecutive subarrays of length size.
 * The final subarray is shorter than size when arr.length is not an exact multiple
 * of size. Must not use lodash's _.chunk.
 *
 * Input  : Array arr (any element type), number size (>= 1).
 * Output : Array of subarrays covering arr left to right, each of length size
 *          except possibly the last.
 *
 * Constraints: 0 <= arr.length <= 1e5; 1 <= size <= arr.length + 1.
 *
 * Approach: walk an index i across arr in strides of size, and at each stride push
 *   the window arr.slice(i, i + size) onto the result. slice clamps its end index to
 *   the array length, so the trailing partial window (when the length is not evenly
 *   divisible) is produced automatically with no special case. An empty arr simply
 *   skips the loop and returns []. slice is a plain Array method, not lodash, so the
 *   restriction is respected.
 *
 * Complexity: O(n) time and O(n) space, n = arr.length -- each element is copied into
 *   exactly one output subarray.
 */

/**
 * @param {Array} arr
 * @param {number} size
 * @return {Array} arr split into consecutive subarrays of length `size`
 */
var chunk = function(arr, size) {
    const result = [];
    // Stride by `size`; slice's end clamps to arr.length, covering the short tail.
    for (let i = 0; i < arr.length; i += size) {
        result.push(arr.slice(i, i + size));
    }
    return result;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = chunk;
