/*
 * LeetCode 2693 - Call Function with Custom Context
 *
 * Add a callPolyfill method to every function (via Function.prototype) that
 * reproduces the behavior of the built-in Function.prototype.call without using
 * call itself. callPolyfill takes a context object as its first argument followed
 * by any number of additional arguments, invokes the function with `this` bound to
 * that context and those arguments forwarded, and returns whatever the function
 * returns.
 *
 * Input  : context (a non-null object) becomes `this`; ...args are the call
 *          arguments. `this` inside callPolyfill is the function being invoked,
 *          since it is called as fn.callPolyfill(...).
 * Output : the value returned by fn when run with the given context and arguments.
 *
 * Constraints: typeof args[0] == 'object' and args[0] != null; 1 <= args.length
 *   <= 100; 2 <= JSON.stringify(args[0]).length <= 1e5.
 *
 * Approach: exploit JavaScript's method-invocation rule -- when a function is called
 *   as obj.method(...), `this` inside it is obj. So temporarily install the target
 *   function (available here as `this`) as a property of context, then call it
 *   through context to make `this` resolve to context, forwarding the spread args.
 *   Use a Symbol as the property key so it can never collide with or overwrite an
 *   existing key on context, then delete it afterward to leave context otherwise
 *   untouched. This uses only ordinary method dispatch -- neither call, apply, nor
 *   bind -- as required.
 *
 * Complexity: O(1) plus the cost of running fn; O(1) extra space (one temporary
 *   Symbol-keyed property).
 */

/**
 * @param {Object} context
 * @param {...*} args
 * @return {null|boolean|number|string|Array|Object}
 */
Function.prototype.callPolyfill = function(context, ...args) {
    // `this` is the function callPolyfill was invoked on. Park it on `context`
    // under a unique Symbol key so no real property of context is clobbered.
    const fnKey = Symbol("callPolyfillFn");
    context[fnKey] = this;

    // Method call: dispatching through context binds `this` to context inside fn.
    const result = context[fnKey](...args);

    // Restore context: remove only the temporary key we added.
    delete context[fnKey];
    return result;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = {};
