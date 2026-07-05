/*
 * LeetCode 2650 - Design Cancellable Function
 *
 * A long-running task is expressed as a generator that only ever yields promises. Write
 * cancellable(generator) returning [cancel, promise]. A driver must run the generator:
 * take each yielded promise, and when it resolves feed the value back with next(value);
 * when it rejects, push the error in with generator.throw(error) so the generator may
 * catch and recover. Calling cancel() rejects the in-flight wait with the string
 * "Cancelled" and throws it into the generator likewise. The returned promise resolves
 * with the generator's final return value, or rejects with any error that escapes it.
 *
 * Input  : generator (a generator object yielding promises).
 * Output : [cancel, promise] -- cancel() aborts the current wait; promise settles with
 *          the generator's outcome.
 *
 * Approach: create one cancelPromise that rejects with "Cancelled" when cancel() runs.
 *   Drive the generator inside an async IIFE: step it, and while it is not done, await
 *   Promise.race([yieldedPromise, cancelPromise]). If the race resolves, resume with
 *   generator.next(value); if it rejects (the yielded promise failed OR cancel fired),
 *   resume with generator.throw(error). A generator that catches the error keeps going;
 *   one that does not lets the error escape -- and since generator.throw on a now-
 *   completed generator re-throws, that error propagates out of the IIFE and rejects the
 *   returned promise. Two correctness points: (1) the driver is an async IIFE, NOT
 *   new Promise(async ...), because an async executor swallows its own throw and would
 *   leave the promise hanging forever on a generator error; (2) cancelPromise.catch()
 *   silences the unhandled rejection that would occur if cancel() fires after the
 *   generator has already finished and the race never observed it.
 *
 * Complexity: O(k) driver steps for a generator that yields k promises; the wall-clock
 *   time is dominated by the awaited promises themselves.
 */

/**
 * @param {Generator} generator
 * @return {[Function, Promise]}
 */
var cancellable = function (generator) {
    let cancel;
    // Rejects with "Cancelled" the moment cancel() is invoked.
    const cancelPromise = new Promise((_, reject) => {
        cancel = () => reject("Cancelled");
    });
    // If cancel() fires after the generator already finished, nothing races the
    // cancelPromise; this handler keeps that stray rejection from going unhandled.
    cancelPromise.catch(() => {});

    const promise = (async () => {
        let next = generator.next();               // may throw if gen fails before yield
        while (!next.done) {
            try {
                // Whichever settles first wins: the yielded work, or cancellation.
                const value = await Promise.race([next.value, cancelPromise]);
                next = generator.next(value);      // resolved -> hand the value back
            } catch (err) {
                // Rejection or cancellation -> let the generator try to handle it. If it
                // does not, generator.throw re-throws and this escapes the IIFE (reject).
                next = generator.throw(err);
            }
        }
        return next.value;                         // generator's return value -> resolve
    })();

    return [cancel, promise];
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = cancellable;
