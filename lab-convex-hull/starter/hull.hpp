// hull.hpp -- TC2038 Lab: Convex Hulls in Practice
// Output convention for every hull function:
//   * only EXTREME points (no collinear points on the edges), no duplicates,
//   * counter-clockwise order,
//   * starting at the lowest point (smallest y; ties -> smallest x).
//   * Degenerate inputs: 0 or 1 distinct point -> those points; all collinear -> its 2 endpoints.
#pragma once
#include <vector>
#include <algorithm>

struct Pt { long long x, y; };
inline bool operator==(const Pt& a, const Pt& b) { return a.x == b.x && a.y == b.y; }
// "lowest, then leftmost" order
inline bool operator<(const Pt& a, const Pt& b) { return a.y < b.y || (a.y == b.y && a.x < b.x); }

// TODO (Part 1): exact orientation test.
//  > 0 : a -> b -> c is a left (counter-clockwise) turn
//  < 0 : right (clockwise) turn
//  = 0 : collinear
// Assume |x|, |y| <= 1e9. Is long long enough? Justify in your report.
inline long long orient(const Pt& a, const Pt& b, const Pt& c) {
    return 0; // TODO
}

inline long long dist2(const Pt& a, const Pt& b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// TODO (Part 1): Graham scan, O(n log n).
std::vector<Pt> graham(std::vector<Pt> P);

// TODO (Part 2): Jarvis march (gift wrapping), O(nh).
// If 'tests' is not null, store the number of orientation tests performed.
std::vector<Pt> jarvis(std::vector<Pt> P, long long* tests = nullptr);
