/*
 * LeetCode 2631 - Group By
 *
 * Enhance every array with a groupBy(fn) method. fn maps an array item to a STRING key;
 * groupBy returns an object whose keys are those produced keys and whose values are the
 * arrays of items that produced each key. Items keep their original relative order
 * inside each group. Any ordering of the keys themselves is acceptable. Solve without
 * lodash's _.groupBy.
 *
 * Input  : fn (item -> string key); `this` is the array being grouped.
 * Output : an object { key: [items...], ... } bucketing items by fn(item).
 *
 * Constraints: 0 <= array.length <= 1e5; fn always returns a string.
 *
 * Approach: walk the array once, compute each item's key via fn, and push the item into
 *   the bucket for that key, creating the bucket the first time the key appears. The one
 *   trap is the key SPACE: fn may legitimately return strings such as "__proto__" or
 *   "constructor". On a normal {} object, "constructor" already exists via the prototype
 *   (so an inherited-key test would misfire) and assigning to "__proto__" retargets the
 *   prototype instead of storing data. Building the result with Object.create(null) gives
 *   a prototype-less object where every string becomes a plain own property, so `key in
 *   grouped` tests only real buckets and even "__proto__" is stored normally.
 *
 * Complexity: O(n) time for a single pass and O(n) space for the grouped output.
 */

/**
 * @param {Function} fn   item -> string group key
 * @return {Object}       map from key to the list of items producing it
 */
Array.prototype.groupBy = function (fn) {
    // Null-prototype object: no inherited keys to collide with, and "__proto__" is a
    // normal own property here rather than the prototype setter.
    const grouped = Object.create(null);

    for (const item of this) {
        const key = fn(item);            // fn returns the string this item groups under
        if (key in grouped) {
            grouped[key].push(item);     // existing bucket: keep original order
        } else {
            grouped[key] = [item];       // first item for this key: start the bucket
        }
    }

    return grouped;
};
