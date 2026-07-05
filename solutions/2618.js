/*
 * LeetCode 2618 - Check if Object Instance of Class
 *
 * Write a function checkIfInstanceOf(obj, classFunction) that returns true when
 * obj is an instance of classFunction OR of any of its superclasses. Because
 * JavaScript has no static types, "instance of" here means: obj has access to the
 * methods that classFunction defines on its prototype. Any value may be passed --
 * obj or classFunction can be null, undefined, a primitive, a plain object, or a
 * constructor function.
 *
 * Input  : obj (any value), classFunction (any value, expected to be a constructor).
 * Output : boolean -- true iff obj can reach classFunction.prototype in its chain.
 *
 * Approach: two guards plus one expression.
 *   1. null / undefined own no prototype chain and cannot be boxed, so they are an
 *      instance of nothing -> false.
 *   2. `instanceof` throws a TypeError when its right operand is not callable, and a
 *      non-function cannot be a constructor anyway, so reject it -> false.
 *   3. Object(obj) leaves real objects untouched but *boxes* primitives (5 becomes a
 *      Number wrapper, "x" a String wrapper), which is exactly what lets a primitive
 *      count as an instance of Number / String / Boolean via its autoboxed methods.
 *      `instanceof` then walks the entire prototype chain, so a subclass instance is
 *      reported as an instance of every ancestor class as well -- superclass support
 *      falls out for free with no manual chain walking.
 *
 * Complexity: O(d) time where d is the prototype-chain depth `instanceof` traverses
 *   (tiny in practice), and O(1) extra space.
 */

/**
 * @param {*} obj
 * @param {*} classFunction
 * @return {boolean}
 */
var checkIfInstanceOf = function(obj, classFunction) {
    // null and undefined have no methods and no boxed object form.
    if (obj === null || obj === undefined) return false;

    // A non-callable "class" can own no instances, and `instanceof` would throw on
    // it -- guard explicitly rather than let it crash.
    if (typeof classFunction !== "function") return false;

    // Object(obj) boxes primitives so their inherited methods count; instanceof then
    // walks the full prototype chain, covering superclasses automatically.
    return Object(obj) instanceof classFunction;
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = checkIfInstanceOf;
