/*
 * LeetCode 497 - Random Point in Non-overlapping Rectangles
 *
 * Given non-overlapping axis-aligned rectangles, each as [a, b, x, y] with (a, b)
 * the bottom-left and (x, y) the top-right corner, implement pick(): return a
 * lattice point [u, v] (integer coordinates) drawn UNIFORMLY from all integer
 * points lying inside or on the border of any rectangle. Because the rectangles
 * never overlap, no point is double-counted.
 *
 * Interface:
 *   Solution(vector<vector<int>>& rects) - store rectangles, precompute weights.
 *   pick()                               - return a uniform random lattice point.
 *
 * Constraints: 1 <= rects.length <= 100; -10^9 <= a < x <= 10^9 and
 *   -10^9 <= b < y <= 10^9; x - a <= 2000 and y - b <= 2000; up to 10^4 picks.
 *
 * Approach: weighted reservoir-free selection via a prefix sum. Rectangle i holds
 *   w*h lattice points, where w = x - a + 1 and h = y - b + 1 (both endpoints are
 *   included, so the count uses +1). Larger rectangles must be chosen more often,
 *   exactly in proportion to their point count, so build an exclusive prefix-sum
 *   array of these counts once. To pick, draw an index k uniformly in [0, total-1]
 *   over the combined point set, binary-search (upper_bound) the prefix array to
 *   learn which rectangle owns index k, then turn the local offset into a cell:
 *   dx = offset % w gives the column and dy = offset / w the row, so the point is
 *   (a + dx, b + dy). Every lattice point maps to exactly one k, hence uniform.
 *
 * Complexity: constructor O(n) time and space; each pick() O(log n) for the binary
 *   search (n <= 100). Counts use 64-bit: total can reach 100 * 2001^2 ~ 4*10^8.
 */

#include <vector>
#include <random>
#include <algorithm>
using namespace std;

class Solution {
public:
    Solution(vector<vector<int>>& rects) : rects(rects), gen(random_device{}()) {
        // prefix[i] = number of lattice points in rectangles 0..i-1 (exclusive),
        // and prefix[n] is the grand total. Width/height add 1 because both the
        // low and high integer coordinates are inside the rectangle.
        prefix.reserve(rects.size() + 1);
        prefix.push_back(0);
        for (const auto& r : rects) {
            long long w = (long long)r[2] - r[0] + 1;   // integer x-values a..x
            long long h = (long long)r[3] - r[1] + 1;   // integer y-values b..y
            prefix.push_back(prefix.back() + w * h);
        }
    }

    vector<int> pick() {
        long long total = prefix.back();
        // Uniform index into the flattened set of every lattice point.
        long long k = uniform_int_distribution<long long>(0, total - 1)(gen);

        // Owning rectangle = first prefix strictly greater than k, minus one.
        int i = (int)(upper_bound(prefix.begin(), prefix.end(), k) - prefix.begin()) - 1;

        // Decode the in-rectangle offset into (column, row) on the lattice.
        long long offset = k - prefix[i];
        const auto& r = rects[i];
        long long w = (long long)r[2] - r[0] + 1;
        int dx = (int)(offset % w);   // 0 .. w-1
        int dy = (int)(offset / w);   // 0 .. h-1
        return { r[0] + dx, r[1] + dy };
    }

private:
    vector<vector<int>> rects;   // rectangles, kept for coordinate decoding
    vector<long long> prefix;    // exclusive prefix sums of lattice-point counts
    mt19937 gen;                 // pseudo-random engine, seeded once
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */
