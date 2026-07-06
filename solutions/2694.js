/*
 * LeetCode 2694 - Event Emitter
 *
 * Design an EventEmitter supporting subscribe and emit.
 *   subscribe(eventName, callback): register callback under eventName. An event may
 *     have many listeners; they fire in subscription order. Returns an object with an
 *     unsubscribe() method that removes exactly this callback and returns undefined.
 *   emit(eventName, args = []): call every callback subscribed to eventName, in
 *     subscription order, spreading args into each. Return the array of their return
 *     values, or [] when nothing is subscribed to that event.
 *
 * Input  : a sequence of subscribe / emit / unsubscribe operations.
 * Output : emit returns the ordered array of callback results; subscribe returns an
 *          { unsubscribe } handle; unsubscribe returns undefined.
 *
 * Constraints: up to 10 operations per test; all operations are valid (e.g. no
 *   unsubscribing a subscription that never existed); callbacks are distinct.
 *
 * Approach: keep a Map from event name to an inner Map of (id -> callback). Every
 *   subscribe draws a globally unique, monotonically increasing id and stores the
 *   callback under it. The unsubscribe handle closes over that inner Map and id and
 *   simply deletes the entry -- deleting by a stable id (rather than by array index)
 *   means removing one listener never shifts the positions of the others, so a later
 *   emit still fires the remaining listeners correctly and in the right order (a JS
 *   Map iterates in insertion order). emit looks up the inner Map, returns [] if the
 *   event is unknown, otherwise calls each callback with the spread args and collects
 *   the results in order.
 *
 * Complexity: subscribe and unsubscribe are O(1); emit is O(k) for k listeners on the
 *   event, plus each callback's own cost. Space is O(total active subscriptions).
 */

class EventEmitter {
    constructor() {
        // eventName -> Map(id -> callback). Inner Map preserves subscription order.
        this.events = new Map();
        // Source of unique subscription ids, shared across all events.
        this.nextId = 0;
    }

    /**
     * @param {string} eventName
     * @param {Function} callback
     * @return {Object} handle exposing unsubscribe()
     */
    subscribe(eventName, callback) {
        // Lazily create the listener map the first time this event is seen.
        if (!this.events.has(eventName)) {
            this.events.set(eventName, new Map());
        }
        const listeners = this.events.get(eventName);
        const id = this.nextId++;      // stable key for this exact subscription
        listeners.set(id, callback);

        return {
            // Delete only this id; safe (and idempotent) even if already removed.
            unsubscribe: () => {
                listeners.delete(id);
                return undefined;
            },
        };
    }

    /**
     * @param {string} eventName
     * @param {Array} args
     * @return {Array} results of each callback, in subscription order
     */
    emit(eventName, args = []) {
        const listeners = this.events.get(eventName);
        if (!listeners) return [];     // no subscribers for this event

        const results = [];
        // Map.values() yields callbacks in the order they were subscribed.
        for (const callback of listeners.values()) {
            results.push(callback(...args));
        }
        return results;
    }
}

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = EventEmitter;
