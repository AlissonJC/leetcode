/*
 * LeetCode 2704 - To Be Or Not To Be
 *
 * Write a tiny test-assertion helper expect(val) that returns an object with two
 * methods:
 *   - toBe(other): returns true when val === other, otherwise throws Error("Not Equal").
 *   - notToBe(other): returns true when val !== other, otherwise throws Error("Equal").
 *
 * Input  : any value val, later compared against another value passed to toBe/notToBe.
 * Output : boolean true on a passing assertion; a thrown Error ("Not Equal" or
 *          "Equal") on a failing one.
 *
 * Constraints: none of note -- val and the compared value may be any JavaScript value.
 *
 * Approach: return an object whose two methods close over val. toBe checks strict
 *   equality (===) and notToBe checks strict inequality (!==); each returns true when
 *   its condition holds and otherwise throws an Error carrying the required message.
 *   Strict comparison is used so no type coercion happens -- e.g. expect(5).toBe("5")
 *   fails, matching how === behaves.
 *
 * Complexity: O(1) time and space per assertion -- a single comparison.
 */

/**
 * @param {*} val
 * @return {{toBe: Function, notToBe: Function}}
 */
var expect = function(val) {
    return {
        // Passes only on strict equality; otherwise signals the mismatch.
        toBe: (other) => {
            if (val === other) return true;
            throw new Error("Not Equal");
        },
        // Passes only on strict inequality; otherwise signals the unwanted match.
        notToBe: (other) => {
            if (val !== other) return true;
            throw new Error("Equal");
        },
    };
};

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = expect;
