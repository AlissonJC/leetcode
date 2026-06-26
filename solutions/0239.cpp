/*
 * LeetCode 239 - Sliding Window Maximum
 *
 * A window of size k slides across nums from left to right, one step at a time.
 * For each of the n - k + 1 positions, report the maximum value visible in the
 * window. Return those maxima in order.
 *
 * Input  : vector<int>& nums (length n), int k (1 <= k <= n).
 * Output : vector<int> of length n - k + 1 — the maximum of each window.
 *
 * Constraints: 1 <= n <= 10^5; -10^4 <= nums[i] <= 10^4; 1 <= k <= n.
 *
 * Approach: a monotonic deque of INDICES, kept so the values they point to are
 *   strictly decreasing from front to back. The front therefore always holds the
 *   index of the current window's maximum. When index i arrives, pop from the back
 *   every index whose value is <= nums[i]: such elements are older and no larger,
 *   so they can never be a maximum again while i sits in the window. Then push i.
 *   Drop the front if it has slid out of the window (front <= i - k). Once the
 *   first full window has formed (i >= k - 1), nums[front] is that window's answer.
 *   Each index is pushed and popped at most once, so the whole scan is linear and
 *   meets the implied O(n) bound for n up to 10^5.
 *
 * Complexity: O(n) time (amortized O(1) per element across deque pushes/pops),
 *   O(k) space for the deque.
 */

#include <vector>
#include <deque>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = (int)nums.size();
        vector<int> result;
        result.reserve(n - k + 1);          // exactly this many windows

        // Holds indices; nums[dq.front()] >= ... >= nums[dq.back()] is maintained.
        deque<int> dq;

        for (int i = 0; i < n; ++i) {
            // Any tail element <= nums[i] is dominated by the newer, larger i and
            // will never be a window maximum again — discard them.
            while (!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            dq.push_back(i);

            // The front may now be the element leaving the window on this step.
            // At most one index can fall out per step, so a single check suffices.
            if (dq.front() <= i - k)
                dq.pop_front();

            // Emit only after the window first covers k elements (indices 0..k-1).
            if (i >= k - 1)
                result.push_back(nums[dq.front()]);
        }

        return result;
    }
};
