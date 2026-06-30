/*
 * LeetCode 3454 - Separate Squares II
 *
 * Each squares[i] = [x, y, l] is an axis-parallel square with bottom-left corner
 * (x, y) and side length l, i.e. it covers [x, x+l] x [y, y+l]. Find the minimum
 * y-coordinate of a horizontal line so that the total area of the squares ABOVE the
 * line equals the total area BELOW it. Squares may overlap, and in this version the
 * overlapping region is counted only once (so "area" means area of the UNION).
 * An answer within 1e-5 of the exact value is accepted.
 *
 * Input  : vector<vector<int>> squares, each {x, y, l}.
 * Output : double — the minimum splitting y-coordinate.
 *
 * Constraints: 1 <= squares.length <= 5e4; 0 <= x, y <= 1e9; 1 <= l <= 1e9; the total
 *   area of all squares does not exceed 1e15. Because x+l can reach ~2e9, coordinates
 *   need 64-bit integers. The union area U <= 1e15 < 2^53, so areas stay exact in both
 *   long long and double. A per-line O(N) area recomputation would be O(N^2) and TLE,
 *   so the union area is built with a sweep + segment tree in O(N log N).
 *
 * Approach: let areaBelow(y) be the area of the union restricted to the halfplane
 *   Y <= y. It rises continuously and monotonically from 0 to the full union area U,
 *   and the line balances the figure exactly when areaBelow(y) = U/2; the smallest
 *   such y is the answer. To build areaBelow, sweep horizontal "slabs" upward between
 *   consecutive square edge-heights. Within a slab the set of active squares is fixed,
 *   so the covered x-length L is constant and the slab adds L * (height) to the area.
 *   L (the length of the union of the active x-intervals) is maintained by the classic
 *   rectangle-union segment tree over compressed x-coordinates: a square contributes a
 *   +1 event on its bottom edge and a -1 on its top edge, and the tree reports the
 *   total x-length currently covered. Accumulate slab areas to get U, then walk the
 *   slabs again until the running area reaches U/2; inside that slab L > 0 and the area
 *   grows linearly, so y* = slabBottom + (U/2 - accumulated) / L. That first crossing
 *   is the minimum balancing y (any flat L=0 gap above it leaves the area unchanged).
 *
 * Complexity: O(N log N) time (sort + N events, each an O(log N) segment-tree update);
 *   O(N) space for coordinates, events, and slabs.
 */

#include <vector>
#include <array>
#include <algorithm>
using namespace std;

class Solution {
public:
    int segCount;            // number of elementary x-intervals
    vector<long long> xs;    // sorted, unique x-coordinates
    vector<int> cnt;         // per-node coverage count added exactly at that node
    vector<long long> cover; // per-node length of x covered (count > 0) within its range

    // Range add of `delta` over elementary x-intervals [ql, qr); node spans [lo, hi).
    void update(int node, int lo, int hi, int ql, int qr, int delta) {
        if (qr <= lo || hi <= ql) return;          // disjoint
        if (ql <= lo && hi <= qr) {
            cnt[node] += delta;                    // node fully inside the query range
        } else {
            int mid = (lo + hi) / 2;
            update(2 * node, lo, mid, ql, qr, delta);
            update(2 * node + 1, mid, hi, ql, qr, delta);
        }
        // A node's covered length is its full x-span if it is currently active at this
        // level; otherwise it is whatever its children cover (0 for an inactive leaf).
        if (cnt[node] > 0)        cover[node] = xs[hi] - xs[lo];
        else if (hi - lo == 1)    cover[node] = 0;
        else                      cover[node] = cover[2 * node] + cover[2 * node + 1];
    }

    double separateSquares(vector<vector<int>>& squares) {
        // Compress x-coordinates: every square edge x and x+l is a potential boundary.
        for (auto& s : squares) {
            xs.push_back((long long)s[0]);
            xs.push_back((long long)s[0] + s[2]);
        }
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        segCount = (int)xs.size() - 1;             // l >= 1 guarantees >= 2 distinct x
        cnt.assign(4 * segCount, 0);
        cover.assign(4 * segCount, 0);

        // One event per horizontal edge: +1 entering at the bottom, -1 leaving at top.
        struct Event { long long y; int ql, qr, delta; };
        vector<Event> ev;
        ev.reserve(squares.size() * 2);
        for (auto& s : squares) {
            long long x = s[0], y = s[1], l = s[2];
            int ql = (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin());
            int qr = (int)(lower_bound(xs.begin(), xs.end(), x + l) - xs.begin());
            ev.push_back({y,     ql, qr, +1});
            ev.push_back({y + l, ql, qr, -1});
        }
        sort(ev.begin(), ev.end(),
             [](const Event& a, const Event& b) { return a.y < b.y; });

        // Sweep upward. Between two consecutive distinct heights the covered length is
        // constant; record that slab and add its area to the running union total.
        vector<array<long long, 3>> slabs;   // {yLo, yHi, coveredLength}
        long long U = 0;
        int E = (int)ev.size(), i = 0;
        long long prevY = ev[0].y;
        while (i < E) {
            long long curY = ev[i].y;
            if (curY != prevY) {
                long long L = cover[1];          // covered x-length during [prevY, curY)
                slabs.push_back({prevY, curY, L});
                U += L * (curY - prevY);
                prevY = curY;
            }
            // Apply every event at this height before measuring the next slab.
            while (i < E && ev[i].y == curY) {
                update(1, 0, segCount, ev[i].ql, ev[i].qr, ev[i].delta);
                ++i;
            }
        }

        // Find the slab where the accumulated area first reaches half of the union.
        double target = U / 2.0;                 // U < 2^53, so this is exact
        long long acc = 0;
        for (auto& s : slabs) {
            long long L = s[2];
            long long slabArea = L * (s[1] - s[0]);
            if ((double)(acc + slabArea) >= target) {
                // L > 0 here (slabArea > 0 was needed to reach target), so the area
                // grows linearly across the slab and the crossing point is exact.
                return (double)s[0] + (target - (double)acc) / (double)L;
            }
            acc += slabArea;
        }
        return (double)prevY;                    // unreachable for valid input
    }
};
