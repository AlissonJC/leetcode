/*
 * LeetCode 2726 - Calculator with Method Chaining
 *
 * Design a Calculator class whose constructor seeds a running result. It offers add,
 * subtract, multiply, divide, and power, each applying its operation to the current
 * result and returning the calculator itself so calls can be chained. divide throws
 * Error("Division by zero is not allowed") when given 0. getResult returns the value.
 *
 * Input  : an initial number, followed by a chain of arithmetic method calls.
 * Output : getResult returns the accumulated number; divide(0) throws.
 *
 * Constraints: 2 <= actions.length <= 2e4; each action is Calculator/add/subtract/
 *   multiply/divide/power/getResult; results within 1e-5 are accepted.
 *
 * Approach: hold a single field result, initialized from the constructor argument.
 *   Every operation updates result in place and returns this -- returning the instance
 *   is what makes chaining like c.add(5).subtract(7) work, since each call yields the
 *   same calculator for the next call. divide guards against a zero divisor and throws
 *   the required error before mutating; power uses the ** operator; getResult just
 *   reads the field back out.
 *
 * Complexity: O(1) time and space per method call.
 */

class Calculator {
    /**
     * @param {number} value
     */
    constructor(value) {
        // The running total; every method reads and rewrites this.
        this.result = value;
    }

    /** @param {number} value @return {Calculator} */
    add(value) {
        this.result += value;
        return this;                       // return this to allow chaining
    }

    /** @param {number} value @return {Calculator} */
    subtract(value) {
        this.result -= value;
        return this;
    }

    /** @param {number} value @return {Calculator} */
    multiply(value) {
        this.result *= value;
        return this;
    }

    /** @param {number} value @return {Calculator} */
    divide(value) {
        // Guard the zero divisor before touching result, per the spec's error message.
        if (value === 0) {
            throw new Error("Division by zero is not allowed");
        }
        this.result /= value;
        return this;
    }

    /** @param {number} value @return {Calculator} */
    power(value) {
        this.result **= value;             // exponentiation: result = result ^ value
        return this;
    }

    /** @return {number} */
    getResult() {
        return this.result;
    }
}

// Exported only so the local test harness can require this file; LeetCode ignores it.
if (typeof module !== "undefined") module.exports = Calculator;
