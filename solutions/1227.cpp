/*
 * LeetCode 1227 - Airplane Seat Assignment Probability
 *
 * n passengers board a plane that has exactly n seats, one assigned per
 * passenger. The first passenger lost the ticket and sits in a uniformly random
 * seat. Everyone after that takes their own assigned seat if it is free, or, if
 * it is already taken, sits in a uniformly random free seat. Return the
 * probability that the n-th passenger ends up in their own assigned seat.
 *
 * Input  : int n. Output : double — the probability for passenger n.
 *
 * Constraints: 1 <= n <= 1e5.
 *
 * Approach: closed form. With n == 1 the lone passenger must sit in seat 1, so
 *   the probability is 1. For n >= 2 it is exactly 1/2. Reason: condition on the
 *   first passenger's pick. Picking seat 1 (prob 1/n) lets everyone sit
 *   correctly, so passenger n succeeds; picking seat n (prob 1/n) dooms
 *   passenger n; picking some middle seat k just hands the same displaced-seat
 *   situation to passenger k over a smaller set of seats. Unrolling this, the
 *   contested choice always collapses to a fair pick between seat 1 and seat n
 *   for the last passenger, and by symmetry each is equally likely. Equivalently
 *   the recurrence f(n) = (1 + sum_{m=2}^{n-1} f(m)) / n gives f(2)=1/2 and then
 *   f(n)=1/2 for every n >= 2 by induction.
 *
 * Complexity: O(1) time and O(1) space.
 */

class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        // n == 1: only one seat exists, so passenger 1 always sits correctly.
        // n >= 2: the last passenger is equally likely to be in seat 1 or seat n.
        return n == 1 ? 1.0 : 0.5;
    }
};
