/*
 * LeetCode 478 - Generate Random Point in a Circle
 *
 * Given a circle by its radius and center, implement randPoint() returning a
 * point drawn UNIFORMLY at random from inside the disk (the boundary counts as
 * inside), as [x, y].
 *
 * Interface:
 *   Solution(radius, x_center, y_center) - store the circle.
 *   randPoint()                          - return a uniform random interior point.
 *
 * Constraints: 0 < radius <= 1e8; -1e7 <= center coords <= 1e7; up to 3*10^4 calls.
 *   Coordinates are doubles; values are modest so precision is not a concern.
 *
 * Approach: sample in polar form, but correct the radial distribution. Choosing
 *   the radius uniformly would over-concentrate points near the center, because a
 *   thin ring at radius rho has area proportional to rho — more area lives at
 *   larger radii. Uniform-over-AREA means the radial cumulative distribution is
 *   proportional to rho^2, so its inverse transform gives rho = radius * sqrt(U)
 *   for U uniform in [0, 1). Pair that with an angle theta uniform in [0, 2*pi)
 *   and convert to Cartesian, offset by the center. This needs exactly two random
 *   draws per call (no rejection loop).
 *
 * Complexity: O(1) time and space per randPoint() call.
 */

#include <vector>
#include <random>
#include <cmath>
using namespace std;

class Solution {
public:
    Solution(double radius, double x_center, double y_center)
        : rad(radius), xc(x_center), yc(y_center),
          gen(random_device{}()), unit(0.0, 1.0) {}

    vector<double> randPoint() {
        // rho = rad * sqrt(U): the sqrt makes the points uniform over area rather
        // than crowding the center (radial CDF is proportional to rho^2).
        double rho = rad * sqrt(unit(gen));
        // Angle uniform over the full circle.
        double theta = 2.0 * PI * unit(gen);
        return { xc + rho * cos(theta), yc + rho * sin(theta) };
    }

private:
    const double PI = acos(-1.0);
    double rad, xc, yc;
    mt19937 gen;                              // pseudo-random engine
    uniform_real_distribution<double> unit;  // U(0, 1)
};
