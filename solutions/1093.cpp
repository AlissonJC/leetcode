/*
 * LeetCode 1093 - Statistics from a Large Sample
 *
 * A sample of integers, each in [0, 255], is given compressed as count[k] = how
 * many times the value k appears. From this frequency table compute five
 * statistics and return them as floating-point numbers in the order
 * [minimum, maximum, mean, median, mode]:
 *   - minimum / maximum : smallest / largest value actually present;
 *   - mean              : sum of all elements divided by how many there are;
 *   - median            : middle value when sorted, or the average of the two
 *                         middle values when the sample size is even;
 *   - mode              : the most frequent value (guaranteed unique).
 *
 * Input  : vector<int> count of length 256. Output : vector<double> of size 5.
 *
 * Constraints: count.length == 256; 0 <= count[i] <= 1e9; 1 <= sum(count) <= 1e9.
 *   The weighted sum reaches up to 255 * 1e9 = 2.55e11, which overflows 32-bit,
 *   so accumulate it in a long long.
 *
 * Approach: one linear pass over the 256 buckets yields minimum (first non-empty
 *   bucket), maximum (last non-empty bucket), mode (bucket with the largest
 *   count), the total element count, and the weighted sum used for the mean.
 *   The median is the value at a given rank in sorted order; since the data is
 *   already a histogram, walk a running cumulative count until it covers the
 *   target rank. Using the two ranks (N+1)/2 and (N+2)/2 (integer division)
 *   handles odd and even N uniformly: for odd N both ranks coincide on the
 *   single middle element, for even N they pick the two middle elements whose
 *   average is the median.
 *
 * Complexity: O(256) = O(1) time (a constant number of passes over the table)
 *   and O(1) extra space.
 */

#include <vector>
using namespace std;

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        int minimum = -1, maximum = -1, mode = 0;
        long long totalCount = 0;   // sum(count[i]); up to 1e9
        long long totalSum   = 0;   // sum(i * count[i]); up to 2.55e11 -> needs 64-bit
        long long maxFreq    = 0;   // largest count seen, to locate the mode

        for (int i = 0; i < 256; ++i) {
            if (count[i] == 0) continue;          // empty bucket contributes nothing

            if (minimum < 0) minimum = i;         // first non-empty bucket is the min
            maximum = i;                          // keep overwriting: last one wins as max

            totalCount += count[i];
            totalSum   += static_cast<long long>(i) * count[i];

            if (count[i] > maxFreq) {             // mode is unique, so a strict > suffices
                maxFreq = count[i];
                mode = i;
            }
        }

        double mean = static_cast<double>(totalSum) / totalCount;

        // The median sits at rank (N+1)/2 for odd N; for even N it averages the
        // two central elements at ranks N/2 and N/2 + 1. Writing the two ranks as
        // (N+1)/2 and (N+2)/2 collapses both cases into one formula.
        double median = (kthValue(count, (totalCount + 1) / 2)
                       + kthValue(count, (totalCount + 2) / 2)) / 2.0;

        return {static_cast<double>(minimum), static_cast<double>(maximum),
                mean, median, static_cast<double>(mode)};
    }

private:
    // Return the value at 1-indexed rank k in the sorted sample, by advancing a
    // cumulative count through the histogram until it reaches k.
    double kthValue(const vector<int>& count, long long k) {
        long long cumulative = 0;
        for (int i = 0; i < 256; ++i) {
            cumulative += count[i];
            if (cumulative >= k) return i;
        }
        return -1.0;  // unreachable given 1 <= k <= sum(count)
    }
};
