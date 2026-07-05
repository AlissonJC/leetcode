/*
 * LeetCode 2622 - Cache With Time Limit
 *
 * Implement a key-value cache where every key carries an expiration. The class
 * exposes three methods:
 *   set(key, value, duration): store value under key; after `duration` ms the key
 *     becomes inaccessible. Returns true if an un-expired key already existed (its
 *     value and duration are both overwritten), false otherwise.
 *   get(key): return the value for an un-expired key, or -1 if none.
 *   count(): return how many keys are currently un-expired.
 *
 * Input/Output: driven by method calls at specific timestamps (LeetCode replays the
 *   sequence with faked timers); each method returns as described above.
 *
 * Approach: keep a Map from key -> { value, timeoutId }. On set, first note whether
 *   the key is already present -- that boolean is the return value. If it is, cancel
 *   its pending expiration with clearTimeout so the OLD timer can no longer delete the
 *   freshly written entry (the crucial correctness point: an overwrite must reset the
 *   clock, not leave a stale deletion armed). Then schedule a new deletion via
 *   setTimeout(..., duration) and store the entry together with that timer's id. get
 *   simply reads the stored value or -1. count returns the Map's size, which is exact
 *   because each expired key removes itself the instant its timer fires.
 *
 * Complexity: set, get, and count are all O(1). Space is O(k) for k un-expired keys.
 */

var TimeLimitedCache = function() {
    // key -> { value, timeoutId }. Presence in the Map means the key is un-expired.
    this.cache = new Map();
};

/**
 * @param {number} key
 * @param {number} value
 * @param {number} duration  time until expiration, in milliseconds
 * @return {boolean} whether an un-expired key already existed
 */
TimeLimitedCache.prototype.set = function(key, value, duration) {
    const alreadyExists = this.cache.has(key);

    // Overwriting a live key: kill its old expiry timer, otherwise that earlier timer
    // would still fire and delete the value we are about to store.
    if (alreadyExists) {
        clearTimeout(this.cache.get(key).timeoutId);
    }

    // Arm a fresh deletion `duration` ms from now, and remember its id so a future
    // overwrite can cancel it.
    const timeoutId = setTimeout(() => this.cache.delete(key), duration);
    this.cache.set(key, { value, timeoutId });

    return alreadyExists;
};

/**
 * @param {number} key
 * @return {number} the value for an un-expired key, or -1
 */
TimeLimitedCache.prototype.get = function(key) {
    // An expired key has already been removed by its timer, so membership == liveness.
    return this.cache.has(key) ? this.cache.get(key).value : -1;
};

/**
 * @return {number} count of currently un-expired keys
 */
TimeLimitedCache.prototype.count = function() {
    // Expired keys self-delete on their timers, so size is exactly the live count.
    return this.cache.size;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = TimeLimitedCache;
