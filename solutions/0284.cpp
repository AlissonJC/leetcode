/*
 * LeetCode 284 - Peeking Iterator
 *
 * Wrap an existing forward iterator (which supports next() and hasNext()) and add a
 * peek() operation that returns the element next() would return, without advancing the
 * iterator. next() and hasNext() must keep their usual meaning.
 *
 * Input  : a sequence of PeekingIterator(nums), peek(), next(), hasNext() operations.
 * Output : peek()/next() return ints; hasNext() returns bool.
 *
 * Constraints: 1 <= nums.length <= 1000; 1 <= nums[i] <= 1000; all peek()/next() calls
 *   are valid; at most 1000 total calls.
 *
 * Approach: the underlying Iterator can only move forward, so to support peeking, cache
 *   one element ahead. peek() pulls the next value from the base iterator the first time
 *   and remembers it (a `peeked` flag), returning the cached value on any repeat peek
 *   without consuming more. next() returns the cached value and clears the flag if a peek
 *   is buffered, otherwise it just advances the base iterator. hasNext() is true when a
 *   value is buffered or the base iterator still has elements.
 *
 * Complexity: O(1) time per operation; O(1) extra space (one buffered element).
 */

#include <vector>
using namespace std;

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *      struct Data;
 *      Data* data;
 *  public:
 *      Iterator(const vector<int>& nums);
 *      Iterator(const Iterator& iter);
 *      // Returns the next element in the iteration.
 *      int next();
 *      // Returns true if the iteration has more elements.
 *      bool hasNext() const;
 *  };
 */

class PeekingIterator : public Iterator {
    bool peeked = false;     // is a look-ahead value currently buffered?
    int peekedVal = 0;       // the buffered value (valid only when peeked == true)

public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums) {}

    // Return the next value without consuming it; buffer it on first peek.
    int peek() {
        if (!peeked) {
            peekedVal = Iterator::next();
            peeked = true;
        }
        return peekedVal;
    }

    int next() {
        if (peeked) {                 // hand back the buffered value and clear it
            peeked = false;
            return peekedVal;
        }
        return Iterator::next();
    }

    bool hasNext() const {
        return peeked || Iterator::hasNext();   // buffered value also counts
    }
};
