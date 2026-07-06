/*
 * LeetCode 2722 - Join Two Arrays by ID
 *
 * Given two arrays arr1 and arr2 of objects, each object carrying a unique integer
 * id, return a single array that joins them on id. The result contains one object per
 * distinct id, sorted ascending by id. An id present in only one array is copied over
 * unchanged. When both arrays have an object for the same id, the two are merged: keys
 * unique to either object are kept, and for keys present in both, arr2's value wins.
 *
 * Input  : Array arr1, Array arr2 (valid JSON; each has unique integer ids).
 * Output : Array joined on id, ascending by id, with arr2 overriding on shared keys.
 *
 * Constraints: within each array ids are unique; 2 <= JSON.stringify(arr) length <= 1e6.
 *
 * Approach: build a Map keyed by id. Seed it with every object from arr1. Walk arr2:
 *   if an id is new, insert the object; if it already exists, replace the stored value
 *   with the SHALLOW merge { ...existing, ...incoming } -- because the spread applies
 *   arr2's keys last, arr2 overrides on collisions, while keys only in arr1 survive.
 *   The merge is shallow by design: a nested object/array under a shared key is taken
 *   wholesale from arr2, not deep-merged (see example 3). Finally emit the Map's values
 *   sorted by id. Using a Map gives O(1) id lookups and dedups ids automatically.
 *
 * Complexity: O(n + m) to index both arrays and O(k log k) to sort the k <= n + m
 *   unique ids; O(k) space for the Map and output.
 */

/**
 * @param {Array} arr1
 * @param {Array} arr2
 * @return {Array}
 */
var join = function(arr1, arr2) {
    // id -> object accumulator; Map keeps lookups O(1) and collapses duplicate ids.
    const byId = new Map();

    // Seed with arr1 as-is.
    for (const obj of arr1) {
        byId.set(obj.id, obj);
    }

    // Fold arr2 in: merge on existing ids (arr2 wins), otherwise insert.
    for (const obj of arr2) {
        if (byId.has(obj.id)) {
            // Spread arr2 last so its keys override; arr1-only keys are preserved.
            byId.set(obj.id, { ...byId.get(obj.id), ...obj });
        } else {
            byId.set(obj.id, obj);
        }
    }

    // Distinct objects, ascending by integer id.
    return [...byId.values()].sort((a, b) => a.id - b.id);
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = join;
