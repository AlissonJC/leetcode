/*
 * LeetCode 900 - RLE Iterator
 *
 * A run-length encoded sequence is given as a flat array: for every pair,
 * encoding[2*i] is a count and encoding[2*i+1] is the value repeated that many
 * times. So [3,8,0,9,2,5] decodes to [8,8,8,5,5] (three 8s, zero 9s, two 5s).
 * Build an iterator that can burn through the decoded sequence in chunks.
 *
 * Input  : a sequence of RLEIterator(encoding), next(n) operations.
 * Output : next(n) exhausts the next n elements of the decoded sequence and returns
 *          the last element exhausted. If fewer than n elements remain, it exhausts
 *          whatever is left and returns -1.
 *
 * Constraints: 2 <= encoding.length <= 1000 (even); 0 <= encoding[i] <= 1e9;
 *   1 <= n <= 1e9; at most 1000 calls to next.
 *
 * Approach: never materialize the decoded sequence (it could be up to ~1e9 long).
 *   Keep an index idx at the current run's count entry (always even) and shrink that
 *   count in place as elements are consumed. Each next(n) walks forward over any runs
 *   that n swallows whole (subtracting their remaining counts and stepping idx += 2),
 *   then, if a run still remains, takes the final n from it (enc[idx] -= n) and returns
 *   that run's value. Runs with count 0 fall through the same loop and are skipped.
 *   If idx runs off the end, the sequence is exhausted and every call returns -1.
 *
 * Note on types: counts and n are each <= 1e9, which fits in a signed 32-bit int, and n
 *   only ever decreases, so plain int cannot overflow here — no need for long long.
 *
 * Complexity: idx only advances forward across the whole object's lifetime, so the total
 *   work over all next() calls is O(R + C) where R = number of runs and C = number of
 *   calls; each individual next() is amortized O(1). O(R) space for the stored encoding.
 */

#include <vector>
using namespace std;

class RLEIterator {
    vector<int> enc;   // own copy of [count0, value0, count1, value1, ...]
    size_t idx = 0;    // even index of the current run's remaining-count entry

public:
    RLEIterator(vector<int>& encoding) : enc(encoding) {}

    int next(int n) {
        // Skip past every run that n exhausts entirely (including any zero-count runs).
        while (idx < enc.size() && n > enc[idx]) {
            n -= enc[idx];       // consume this run's whole remaining count
            idx += 2;            // advance to the next (count, value) pair
        }
        if (idx >= enc.size())
            return -1;           // ran off the end: fewer than n elements were left
        enc[idx] -= n;           // take the final n elements from the current run
        return enc[idx + 1];     // value of the last element exhausted
    }
};

/**
 * Your RLEIterator object will be instantiated and called as such:
 * RLEIterator* obj = new RLEIterator(encoding);
 * int param_1 = obj->next(n);
 */
