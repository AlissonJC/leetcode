/*
 * LeetCode 2649 - Nested Array Generator
 *
 * A multi-dimensional array holds integers and/or other multi-dimensional arrays. Return
 * a generator that yields all of its integers in inorder-traversal order: scan each array
 * left to right, yielding an integer directly or, on encountering a sub-array, yielding
 * everything inside it (recursively) before moving on.
 *
 * Input  : arr, a nested array of integers.
 * Output : a generator producing the integers in left-to-right, depth-first order.
 *
 * Constraints: total integers 0..1e5; values 0..1e5; maxNestingDepth up to 1e5.
 *
 * Approach: the natural solution -- a generator that does `yield* inorderTraversal(sub)`
 *   on each sub-array -- is elegant but unsafe here: yield* chains one delegating
 *   generator per nesting level, so pulling a value from a deeply nested chain recurses
 *   on the CALL STACK to that depth and overflows well before the allowed depth of 1e5.
 *   Instead, drive the traversal with an explicit stack of array iterators. Start with
 *   the top array's iterator; each step advances the topmost iterator: if it is exhausted
 *   pop it, if it produces a sub-array push that array's iterator (descend one level), and
 *   if it produces an integer yield it. All nesting now lives in the heap-allocated stack,
 *   so a single ordinary generator handles any depth without growing the call stack.
 *
 * Complexity: O(n) total work to walk every integer and array node once, and O(d) space
 *   for the iterator stack where d is the maximum nesting depth.
 */

/**
 * @param {Array} arr   a (possibly nested) array of integers
 * @return {Generator<number>}
 */
var inorderTraversal = function* (arr) {
    // Stack of active array iterators; the top is the array we are currently scanning.
    const stack = [arr[Symbol.iterator]()];

    while (stack.length > 0) {
        const { value, done } = stack[stack.length - 1].next();

        if (done) {
            stack.pop();                              // finished this array; go back up
        } else if (Array.isArray(value)) {
            stack.push(value[Symbol.iterator]());     // descend into the sub-array
        } else {
            yield value;                              // a plain integer: emit it
        }
    }
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = inorderTraversal;
